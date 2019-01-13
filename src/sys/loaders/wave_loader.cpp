#include "sys/loaders/wave_loader.h"
#include "fs/file.h"
#include "mem.h"
#include "log.h"

namespace dk::sys
{

status wave_loader::load(audio::sound_data& res, string_view file_path) noexcept
{
	//  TODO: write timer
	fs::file wave;
	if (auto ret = wave.open(file_path); !ret)
		return status::ERROR;

	size_t readed_size;
	size_t RIFF_chunk_size = 0;
	size_t total_chunks_size = 0;
	wave_header::chunk_header chunk_header;

	while ((readed_size = wave.read(chunk_header)) == sizeof(chunk_header)) {
		switch (chunk_header.id) {
			case wave_header::RIFF_chunk::id: {
				wave_header::RIFF_chunk RIFF_chunk;
				if (wave.read(RIFF_chunk) != sizeof(RIFF_chunk)) {
					DK_LOG_ERROR("Failed to read RIFF chunk from WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				if (RIFF_chunk.format != wave_header::RIFF_chunk::WAVE_format) {
					DK_LOG_ERROR("Wrong format in RIFF chunk of WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				RIFF_chunk_size = chunk_header.size;
				break;
			}
			case wave_header::fmt_chunk::id: {
				wave_header::fmt_chunk fmt_chunk;
				if (wave.read(fmt_chunk) != sizeof(fmt_chunk)) {
					DK_LOG_ERROR("Failed to read fmt chunk from WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				if (chunk_header.size != sizeof(wave_header::fmt_chunk)) { /* PCM encoding format header size */
					if (chunk_header.size == sizeof(wave_header::fmt_chunk) + sizeof(uint16_t) /* extra param size */) {
						uint16_t extra_param_size;
						if (wave.read(extra_param_size) != sizeof(extra_param_size)) {
							DK_LOG_ERROR("Failed to read fmt chunk extra param size from WAVE file '", file_path, '\'');
							return status::ERROR;
						}

						total_chunks_size += extra_param_size;
						wave.move_cursor(wave_header::align_chunk(extra_param_size));
					} else {
						DK_LOG_ERROR("Unexpected fmt sub chunk size in WAVE file '", file_path, '\'');
						return status::ERROR;
					}
				}

				if (fmt_chunk.audio_fmt != 1) { /* PCM must be 1 - linear quantization */
					DK_LOG_ERROR("Compressed WAVE file '", file_path, "' does not supported");
					return status::ERROR;
				}

				res.set_num_channels(fmt_chunk.num_channels);
				res.set_sample_rate(fmt_chunk.sample_rate);
				res.set_bits_per_sample(fmt_chunk.bits_per_sample);
				total_chunks_size += chunk_header.size + sizeof(wave_header::chunk_header);
				break;
			}
			case wave_header::data_chunk::id: {
				res.set_data((uint8_t*)mem_alloc(chunk_header.size));
				if (wave.read(res.data(), chunk_header.size) != chunk_header.size) {
					DK_LOG_ERROR("Failed to read WAVE file '", file_path, "' data");
					return status::ERROR;;
				}

				res.set_size(chunk_header.size);
				total_chunks_size += chunk_header.size + sizeof(wave_header::chunk_header);
				break;
			}
			case wave_header::LIST_chunk::id: {
				char chunk[chunk_header.size];
				if (wave.read(chunk, wave_header::align_chunk(chunk_header.size)) != chunk_header.size) {
					DK_LOG_ERROR("Failed to read LIST chunk from WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				const char* sub_chunk_data = chunk;
				size_t sub_chunk_size = chunk_header.size;
				auto read_from_chuck = [&sub_chunk_data, &sub_chunk_size](size_t size) {
					if (size > sub_chunk_size)
						return false;

					sub_chunk_size -= size;
					sub_chunk_data += size;
					return true;
				};

				auto LIST_chunk = (const wave_header::LIST_chunk*)sub_chunk_data;
				if (!read_from_chuck(sizeof(wave_header::LIST_chunk))) {
					DK_LOG_ERROR("Failed to read LIST chunk type from WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				total_chunks_size += chunk_header.size + sizeof(wave_header::chunk_header);
				if (LIST_chunk->type != wave_header::LIST_chunk::INFO_type) {
					string_view type_str((const char*)&LIST_chunk->type, sizeof(LIST_chunk->type));
					DK_LOG_WARNING("Unknown LIST chunk type '", type_str, "' in WAVE file '", file_path, '\'');
					break;
				}

				DK_LOG("WAVE file '", file_path, "' info:");
				while (sub_chunk_size) {
					auto sub_chunk_header = (const wave_header::chunk_header*)sub_chunk_data;
					if (!read_from_chuck(sizeof(wave_header::chunk_header))) {
						DK_LOG_ERROR("Failed to read LIST sub chunk header from WAVE file '", file_path, '\'');
						return status::ERROR;
					}

					auto info_data = sub_chunk_data;
					if (!read_from_chuck(wave_header::align_chunk(sub_chunk_header->size))) {
						DK_LOG_ERROR("Failed to read LIST sub chunk data from WAVE file '", file_path, '\'');
						return status::ERROR;
					}

					string_view info(info_data, sub_chunk_header->size - 1 /* to skip '\0' at the end */);
					switch (sub_chunk_header->id) {
						case wave_header::LIST_chunk::artist_info:        DK_LOG_PRINT("\tartist:         ", info); break;
						case wave_header::LIST_chunk::name_info:          DK_LOG_PRINT("\tname:           ", info); break;
						case wave_header::LIST_chunk::creation_date_info: DK_LOG_PRINT("\tcreation date:  ", info); break;
						case wave_header::LIST_chunk::comments_info:      DK_LOG_PRINT("\tcomments:       ", info); break;
						case wave_header::LIST_chunk::copyright_info:     DK_LOG_PRINT("\tcopyright:      ", info); break;
						case wave_header::LIST_chunk::product_info:       DK_LOG_PRINT("\tproduct:        ", info); break;
						case wave_header::LIST_chunk::software_info:      DK_LOG_PRINT("\tsoftware:       ", info); break;
						default:
							DK_LOG_PRINT("\tunknown '", string_view((const char*)&sub_chunk_header->id,
								sizeof(sub_chunk_header->id)), "': ", info);
					}
				}

				break;
			}
			default:
				string_view id_str((const char*)&chunk_header.id, sizeof(chunk_header.id));
				DK_LOG_WARNING("Unknown chunk id '", id_str, "' in WAVE file '", file_path, '\'');

				total_chunks_size += chunk_header.size + sizeof(wave_header::chunk_header);
				if (auto ret = wave.move_cursor(chunk_header.size); !ret)
					return status::ERROR;
		}
	}

	if (readed_size != fs::file::END_OF_FILE) {
		if (readed_size != fs::file::BAD_SIZE)
			DK_LOG_ERROR("Failed to read chunk header from WAVE file '", file_path, '\'');

		return status::ERROR;
	}

	if (RIFF_chunk_size != sizeof(wave_header::chunk_header::id) /* RIFF chunk id */ + total_chunks_size) {
		DK_LOG_ERROR("Chunks size check failed in header of WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	DK_LOG_OK(
		"WAVE data created from file '", file_path, "':\n"
		"\tnum channels:    ", res.num_channels(), '\n',
		"\tsample rate:     ", res.sample_rate(), '\n',
		"\tbits per sample: ", res.bits_per_sample()
	);

	return status::OK;
}

status wave_loader::load(audio::sound& res, string_view file_path) noexcept
{
	audio::sound_data sound_data;
	if (auto ret = load(sound_data, file_path); !ret)
		return ret;

	return res.create(sound_data);
}

resource* wave_loader::load(string_view file_path, resource_type type) noexcept /* override */
{
	if (type == resource_type::SOUND_DATA) {
		audio::sound_data* sound_data = mem_create(audio::sound_data);
		if (!load(*sound_data, file_path)) {
			mem_destroy(sound_data);
			return nullptr;
		}

		return sound_data;
	} else if (type == resource_type::SOUND) {
		audio::sound* sound = mem_create(audio::sound);
		if (!load(*sound, file_path)) {
			mem_destroy(sound);
			return nullptr;
		}

		return sound;
	}

	DK_LOG_ERROR("WAVE loader does not support this resource type: #", (uint32_t)type);
	return nullptr;
}

status wave_loader::load(resource& res, string_view file_path, resource_type type) noexcept /* override */
{
	if (type == resource_type::SOUND_DATA) return load(static_cast<audio::sound_data&>(res), file_path);
	else if (type == resource_type::SOUND) return load(static_cast<audio::sound&>(res), file_path);

	DK_LOG_ERROR("WAVE loader does not support this resource type: #", (uint32_t)type);
	return status::ERROR;
}

}
