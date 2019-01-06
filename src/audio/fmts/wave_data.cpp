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

	struct
	{
		chunk_header chunk;
		uint32_t     format;
	} RIFF;

	struct
	{
		chunk_header sub_chunk;
		uint16_t     audio_fmt;       /* PCM = 1 */
		uint16_t     num_channels;    /* mono = 1, stereo = 2, ... */
		uint32_t     sample_rate;     /* 8000, 44100, ... */
		uint32_t     byte_rate;       /* sample_rate * num_channels * bits_per_sample / 8 */
		uint16_t     block_align;     /* num_channels * bits_per_sample / 8 */
		uint16_t     bits_per_sample; /* 8, 16, ... */
	} fmt;

	struct
	{
		chunk_header sub_chunk; /* size = num_samples (yeah, samples) * num_channels * bits_per_sample / 8 */
	} data;
};

status sound_data::load_wave(string_view file_path) noexcept
{
	//  TODO: WAVE file may have additional subchunks.
	//  If so, each will have a char[4] SubChunkID, and
	//  unsigned long SubChunkSize, and SubChunkSize amount of data

	//  TODO: write timer
	fs::file wave;
	if (auto res = wave.open(file_path); !res)
		return res;

	wave_header head;
	if (auto res = wave.read((uint8_t*)&head, sizeof(head)); !res) {
		DK_LOG_ERROR("Failed to read WAVE file '", file_path, "' header");
		return res;
	}

	if (head.RIFF.chunk.id != 0x46464952) { /* "RIFF" */
		DK_LOG_ERROR("Wrong RIFF chunk ID in WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	if (head.RIFF.format != 0x45564157) { /* "WAVE" */
		DK_LOG_ERROR("Wrong format in RIFF chunk of WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	if (head.fmt.sub_chunk.id != 0x20746D66) { /* "fmt " */
		DK_LOG_ERROR("Wrong fmt sub chunk ID in WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	if (head.fmt.sub_chunk.size != 16) { /* PCM encoding format header size */
		DK_LOG_ERROR("Unexpected fmt sub chunk size in WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	if (head.fmt.audio_fmt != 1) { /* PCM must be 1 - linear quantization */
		DK_LOG_ERROR("Compressed WAVE file '", file_path, "' does not supported");
		return status::ERROR;
	}

	if (head.data.sub_chunk.id != 0x61746164) { /* "data" */
		DK_LOG_ERROR("Wrong data sub chunk ID in WAVE file '", file_path, '\'');
		return status::ERROR;
	}

	if (head.RIFF.chunk.size != sizeof(head.RIFF.chunk.id)
			+ (sizeof(wave_header::chunk_header) + head.fmt.sub_chunk.size)
			+ (sizeof(wave_header::chunk_header) + head.data.sub_chunk.size)) {
		DK_LOG_ERROR("Invalid size in WAVE file '", file_path, "' header");
	}

	m_data = mem::alloc(head.data.sub_chunk.size);
	if (auto res = wave.read(m_data, head.data.sub_chunk.size); !res) {
		DK_LOG_ERROR("Failed to read WAVE file '", file_path, "' data");
		return res;
	}

	m_size = head.data.sub_chunk.size;
	m_num_channels = head.fmt.num_channels;
	m_sample_rate = head.fmt.sample_rate;
	m_bits_per_sample = head.fmt.bits_per_sample;

	DK_LOG_OK("WAVE file '", file_path, "' loaded");
	return status::OK;
}

}
