#ifndef __DK_AUDIO_SOUND_DATA_H__
#define __DK_AUDIO_SOUND_DATA_H__

#include "resource.h"
#include "containers/string_view.h"

namespace dk::audio
{

enum class sound_data_fmt
{
	AUTO = 0,
	WAVE
};

class sound_data final: public resource
{
private:
	friend class resource_manager;

	uint8_t* m_data;
	size_t   m_size;
	uint32_t m_num_channels;
	uint32_t m_sample_rate;
	uint32_t m_bits_per_sample;

	status load_wave(string_view file_path) noexcept;

public:
	sound_data() noexcept;
	~sound_data() noexcept override;

	const uint8_t* data() const noexcept { return m_data; }
	size_t size() const noexcept { return m_size; }
	uint32_t num_channels() const noexcept { return m_num_channels; }
	uint32_t sample_rate() const noexcept { return m_sample_rate; }
	uint32_t bits_per_sample() const noexcept { return m_bits_per_sample; }

	status create(string_view file_path, sound_data_fmt fmt = sound_data_fmt::AUTO) noexcept;
};

}

#endif  //  !__DK_AUDIO_SOUND_DATA_H__
