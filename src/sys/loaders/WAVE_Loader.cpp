#include "sys/loaders/WAVE_Loader.h"
#include "fs/File.h"
#include "Mem.h"
#include "Log.h"

namespace dk::sys
{

Status WAVE_Loader::load(audio::SoundData& sound_data, StringView file_path) noexcept
{
	//  TODO: write timer
	fs::File WAVE;
	if (auto ret = WAVE.open(file_path); !ret)
		return Status::ERROR;

	size_t readed_size;
	size_t RIFF_chunk_size = 0;
	size_t total_chunks_size = 0;
	WAVE_Header::ChunkHeader chunk_header;

	while ((readed_size = WAVE.read(chunk_header)) == sizeof(chunk_header)) {
		switch (chunk_header.id) {
			case WAVE_Header::RIFF_chunk::id: {
				WAVE_Header::RIFF_chunk RIFF_chunk;
				if (WAVE.read(RIFF_chunk) != sizeof(RIFF_chunk)) {
					DK_LOG_ERROR("Failed to read RIFF chunk from WAVE file '", file_path, '\'');
					return Status::ERROR;
				}

				if (RIFF_chunk.format != WAVE_Header::RIFF_chunk::WAVE_format) {
					DK_LOG_ERROR("Wrong format in RIFF chunk of WAVE file '", file_path, '\'');
					return Status::ERROR;
				}

				RIFF_chunk_size = chunk_header.size;
				break;
			}
			case WAVE_Header::fmt_chunk::id: {
				WAVE_Header::fmt_chunk fmt_chunk;
				if (WAVE.read(fmt_chunk) != sizeof(fmt_chunk)) {
					DK_LOG_ERROR("Failed to read fmt chunk from WAVE file '", file_path, '\'');
					return Status::ERROR;
				}

				if (chunk_header.size != sizeof(WAVE_Header::fmt_chunk)) { /* PCM encoding format header size */
					if (chunk_header.size == sizeof(WAVE_Header::fmt_chunk) + sizeof(uint16_t) /* extra param size */) {
						uint16_t extra_param_size;
						if (WAVE.read(extra_param_size) != sizeof(extra_param_size)) {
							DK_LOG_ERROR("Failed to read fmt chunk extra param size from WAVE file '", file_path, '\'');
							return Status::ERROR;
						}

						total_chunks_size += extra_param_size;
						WAVE.move_cursor(WAVE_Header::align_chunk(extra_param_size));
					} else {
						DK_LOG_ERROR("Unexpected fmt sub chunk size in WAVE file '", file_path, '\'');
						return Status::ERROR;
					}
				}

				if (fmt_chunk.audio_fmt != 1) { /* PCM must be 1 - linear quantization */
					DK_LOG_ERROR("Compressed WAVE file '", file_path, "' does not supported");
					return Status::ERROR;
				}

				sound_data.set_num_channels(fmt_chunk.num_channels);
				sound_data.set_sample_rate(fmt_chunk.sample_rate);
				sound_data.set_bits_per_sample(fmt_chunk.bits_per_sample);
				total_chunks_size += chunk_header.size + sizeof(WAVE_Header::ChunkHeader);
				break;
			}
			case WAVE_Header::data_chunk::id: {
				sound_data.set_data((uint8_t*)mem_alloc(chunk_header.size));
				if (WAVE.read(sound_data.data(), chunk_header.size) != chunk_header.size) {
					DK_LOG_ERROR("Failed to read WAVE file '", file_path, "' data");
					return Status::ERROR;;
				}

				sound_data.set_size(chunk_header.size);
				total_chunks_size += chunk_header.size + sizeof(WAVE_Header::ChunkHeader);
				break;
			}
			case WAVE_Header::LIST_chunk::id: {
				char chunk[chunk_header.size];
				if (WAVE.read(chunk, WAVE_Header::align_chunk(chunk_header.size)) != chunk_header.size) {
					DK_LOG_ERROR("Failed to read LIST chunk from WAVE file '", file_path, '\'');
					return Status::ERROR;
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

				auto LIST_chunk = (const WAVE_Header::LIST_chunk*)sub_chunk_data;
				if (!read_from_chuck(sizeof(WAVE_Header::LIST_chunk))) {
					DK_LOG_ERROR("Failed to read LIST chunk type from WAVE file '", file_path, '\'');
					return Status::ERROR;
				}

				total_chunks_size += chunk_header.size + sizeof(WAVE_Header::ChunkHeader);
				if (LIST_chunk->type != WAVE_Header::LIST_chunk::INFO_type) {
					StringView type_str((const char*)&LIST_chunk->type, sizeof(LIST_chunk->type));
					DK_LOG_WARNING("Unknown LIST chunk type '", type_str, "' in WAVE file '", file_path, '\'');
					break;
				}

				DK_LOG("WAVE file '", file_path, "' info:");
				while (sub_chunk_size) {
					auto sub_chunk_header = (const WAVE_Header::ChunkHeader*)sub_chunk_data;
					if (!read_from_chuck(sizeof(WAVE_Header::ChunkHeader))) {
						DK_LOG_ERROR("Failed to read LIST sub chunk header from WAVE file '", file_path, '\'');
						return Status::ERROR;
					}

					auto info_data = sub_chunk_data;
					if (!read_from_chuck(WAVE_Header::align_chunk(sub_chunk_header->size))) {
						DK_LOG_ERROR("Failed to read LIST sub chunk data from WAVE file '", file_path, '\'');
						return Status::ERROR;
					}

					StringView info(info_data, sub_chunk_header->size - 1 /* to skip '\0' at the end */);
					switch (sub_chunk_header->id) {
						case WAVE_Header::LIST_chunk::artist_info:        DK_LOG_PRINT("\tartist:         ", info); break;
						case WAVE_Header::LIST_chunk::name_info:          DK_LOG_PRINT("\tname:           ", info); break;
						case WAVE_Header::LIST_chunk::creation_date_info: DK_LOG_PRINT("\tcreation date:  ", info); break;
						case WAVE_Header::LIST_chunk::comments_info:      DK_LOG_PRINT("\tcomments:       ", info); break;
						case WAVE_Header::LIST_chunk::copyright_info:     DK_LOG_PRINT("\tcopyright:      ", info); break;
						case WAVE_Header::LIST_chunk::product_info:       DK_LOG_PRINT("\tproduct:        ", info); break;
						case WAVE_Header::LIST_chunk::software_info:      DK_LOG_PRINT("\tsoftware:       ", info); break;
						default:
							DK_LOG_PRINT("\tunknown '", StringView((const char*)&sub_chunk_header->id,
								sizeof(sub_chunk_header->id)), "': ", info);
					}
				}

				break;
			}
			default:
				StringView id_str((const char*)&chunk_header.id, sizeof(chunk_header.id));
				DK_LOG_WARNING("Unknown chunk id '", id_str, "' in WAVE file '", file_path, '\'');

				total_chunks_size += chunk_header.size + sizeof(WAVE_Header::ChunkHeader);
				if (auto ret = WAVE.move_cursor(chunk_header.size); !ret)
					return Status::ERROR;
		}
	}

	if (readed_size != fs::File::END_OF_FILE) {
		if (readed_size != fs::File::BAD_SIZE)
			DK_LOG_ERROR("Failed to read chunk header from WAVE file '", file_path, '\'');

		return Status::ERROR;
	}

	if (RIFF_chunk_size != sizeof(WAVE_Header::ChunkHeader::id) /* RIFF chunk id */ + total_chunks_size) {
		DK_LOG_ERROR("Chunks size check failed in header of WAVE file '", file_path, '\'');
		return Status::ERROR;
	}

	DK_LOG_OK(
		"WAVE data created from file '", file_path, "':\n"
		"\tnum channels:    ", sound_data.num_channels(), '\n',
		"\tsample rate:     ", sound_data.sample_rate(), '\n',
		"\tbits per sample: ", sound_data.bits_per_sample()
	);

	return Status::OK;
}

Status WAVE_Loader::load(audio::Sound& sound, StringView file_path) noexcept
{
	audio::SoundData sound_data;
	if (auto ret = load(sound_data, file_path); !ret)
		return ret;

	return sound.create(sound_data);
}

Resource* WAVE_Loader::load(StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::SOUND_DATA) {
		audio::SoundData* sound_data = mem_create(audio::SoundData);
		if (!load(*sound_data, file_path)) {
			mem_destroy(sound_data);
			return nullptr;
		}

		return sound_data;
	} else if (type == ResourceType::SOUND) {
		audio::Sound* sound = mem_create(audio::Sound);
		if (!load(*sound, file_path)) {
			mem_destroy(sound);
			return nullptr;
		}

		return sound;
	}

	DK_LOG_ERROR("WAVE loader does not support this resource type: #", (uint32_t)type);
	return nullptr;
}

Status WAVE_Loader::load(Resource& res, StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::SOUND_DATA) return load(static_cast<audio::SoundData&>(res), file_path);
	else if (type == ResourceType::SOUND) return load(static_cast<audio::Sound&>(res), file_path);

	DK_LOG_ERROR("WAVE loader does not support this resource type: #", (uint32_t)type);
	return Status::ERROR;
}

}
