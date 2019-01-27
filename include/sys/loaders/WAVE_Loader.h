#ifndef __DK_SYS_WAVE_LOADER_H__
#define __DK_SYS_WAVE_LOADER_H__

#include "audio/Sound.h"
#include "sys/ResourceLoader.h"

#define WAVE_CHUNK_ID(id) (id[0] + (id[1] << 8) + (id[2] << 16) + (id[3] << 24))

namespace dk::sys
{

struct WAVE_Header
{
	struct ChunkHeader
	{
		uint32_t id;
		uint32_t size;
	};

	struct RIFF_chunk
	{
		static constexpr uint32_t id          = WAVE_CHUNK_ID("RIFF"); /* 0x46464952 */
		static constexpr uint32_t WAVE_format = WAVE_CHUNK_ID("WAVE"); /* 0x45564157 */
		uint32_t format;
	};

	struct LIST_chunk
	{
		static constexpr uint32_t id        = WAVE_CHUNK_ID("LIST"); /* 0x5453494C */
		static constexpr uint32_t INFO_type = WAVE_CHUNK_ID("INFO"); /* 0x4F464E49 */

		/* sub chunk ids */
		static constexpr uint32_t artist_info        = WAVE_CHUNK_ID("IART");
		static constexpr uint32_t comments_info      = WAVE_CHUNK_ID("ICMT");
		static constexpr uint32_t copyright_info     = WAVE_CHUNK_ID("ICOP");
		static constexpr uint32_t creation_date_info = WAVE_CHUNK_ID("ICRD");
		static constexpr uint32_t name_info          = WAVE_CHUNK_ID("INAM");
		static constexpr uint32_t product_info       = WAVE_CHUNK_ID("IPRD");
		static constexpr uint32_t software_info      = WAVE_CHUNK_ID("ISFT");

		uint32_t type;
	};

	struct fmt_chunk
	{
		static constexpr uint32_t id = WAVE_CHUNK_ID("fmt "); /* 0x20746D66 */

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
		static constexpr uint32_t id = WAVE_CHUNK_ID("data"); /* 0x61746164 */
	};

	static size_t align_chunk(size_t size) noexcept
	{
		return size + (size & 1); /* every chunk must me aligned by 16-bit boundaries */
	}
};

class WAVE_Loader final: public ResourceLoader
{
public:
	Status load(audio::SoundData& sound_data, StringView file_path) noexcept;
	Status load(audio::Sound& sound, StringView file_path) noexcept;

	Resource* load(StringView file_path, ResourceType type) noexcept override;
	Status    load(Resource& res, StringView file_path, ResourceType type) noexcept override;
};

}

#endif  //  !__DK_SYS_WAVE_LOADER_H__
