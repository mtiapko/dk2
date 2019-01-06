#include "log.h"
#include "mem.h"
#include "fs/file.h"
#include "audio/source_data.h"

namespace dk::audio
{

struct wave_header
{
	struct chunk_header
	{
		uint32_t id;
		uint32_t size;
	};

	struct RIFF_chunk
	{
		static constexpr uint32_t id = 0x46464952; /* "RIFF" */
		uint32_t format;
	};

	struct fmt_chunk
	{
		static constexpr uint32_t id = 0x20746D66; /* "fmt " */

		uint16_t     audio_fmt;       /* PCM = 1 */
		uint16_t     num_channels;    /* mono = 1, stereo = 2, ... */
		uint32_t     sample_rate;     /* 8000, 44100, ... */
		uint32_t     byte_rate;       /* sample_rate * num_channels * bits_per_sample / 8 */
		uint16_t     block_align;     /* num_channels * bits_per_sample / 8 */
		uint16_t     bits_per_sample; /* 8, 16, ... */
	};

	struct data_chunk
	{
		/* size = num_samples (yeah, samples) * num_channels * bits_per_sample / 8 */
		static constexpr uint32_t id = 0x61746164; /* "data" */
	};
};

status sound_data::load_wave(string_view file_path) noexcept
{
	//  TODO: write timer
	fs::file wave;
	if (auto res = wave.open(file_path); !res)
		return res;

	size_t readed_size;
	size_t RIFF_chunk_size = 0;
	size_t fmt_chunk_size = 0;
	size_t data_chunk_size = 0;
	size_t unknown_chunk_size = 0;
	wave_header::chunk_header chunk_header;
	while ((readed_size = wave.read(chunk_header)) == sizeof(chunk_header)) {
		switch (chunk_header.id) {
			case wave_header::RIFF_chunk::id: {
				wave_header::RIFF_chunk RIFF_chunk;
				if (wave.read(RIFF_chunk) != sizeof(RIFF_chunk)) {
					return status::ERROR;
				}

				if (RIFF_chunk.format != 0x45564157) { /* "WAVE" */
					DK_LOG_ERROR("Wrong format in RIFF chunk of WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				RIFF_chunk_size = chunk_header.size;
				break;
			}
			case wave_header::fmt_chunk::id: {
				wave_header::fmt_chunk fmt_chunk;
				if (wave.read(fmt_chunk) != sizeof(fmt_chunk)) {
					return status::ERROR;
				}

				if (chunk_header.size != 16) { /* PCM encoding format header size */
					DK_LOG_ERROR("Unexpected fmt sub chunk size in WAVE file '", file_path, '\'');
					return status::ERROR;
				}

				if (fmt_chunk.audio_fmt != 1) { /* PCM must be 1 - linear quantization */
					DK_LOG_ERROR("Compressed WAVE file '", file_path, "' does not supported");
					return status::ERROR;
				}

				m_num_channels = fmt_chunk.num_channels;
				m_sample_rate = fmt_chunk.sample_rate;
				m_bits_per_sample = fmt_chunk.bits_per_sample;
				fmt_chunk_size = chunk_header.size + sizeof(wave_header::chunk_header);
				break;
			}
			case wave_header::data_chunk::id: {
				m_data = (uint8_t*)mem::alloc(chunk_header.size);
				if (auto res = wave.read(m_data, chunk_header.size); !res) {
					DK_LOG_ERROR("Failed to read WAVE file '", file_path, "' data");
					return res;
				}

				m_size = chunk_header.size;
				data_chunk_size = chunk_header.size + sizeof(wave_header::chunk_header);
				break;
			}
			default:
				unknown_chunk_size += chunk_header.size + sizeof(wave_header::chunk_header);
				DK_LOG_WARNING("Unknown chunk id in WAVE file '", file_path, '\'');
				if (auto res = wave.move_cursor(chunk_header.size); !res)
					return res;
		}
	}

	if (readed_size == fs::file::BAD_SIZE)
		return status::ERROR;

	if (RIFF_chunk_size != sizeof(wave_header::chunk_header::id) /* RIFF chunk id */
			+ fmt_chunk_size + data_chunk_size + unknown_chunk_size) {
		DK_LOG_ERROR("Chunks size check failed in header of WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	DK_LOG_OK("WAVE file '", file_path, "' loaded");
	return status::OK;
}

}
