#ifndef __DK_AUDIO_SOUND_DATA_H__
#define __DK_AUDIO_SOUND_DATA_H__

#include <stdint.h>
#include <stddef.h>
#include "resource.h"

namespace dk::audio
{

class sound_data final: public resource
{
private:
	uint8_t* m_data;
	size_t   m_size;
	uint32_t m_num_channels;
	uint32_t m_sample_rate;
	uint32_t m_bits_per_sample;

public:
	sound_data() noexcept;
	~sound_data() noexcept override;

	static resource_type type() noexcept { return resource_type::SOUND_DATA; }

	uint8_t* data() const noexcept { return m_data; }
	size_t size() const noexcept { return m_size; }
	uint32_t num_channels() const noexcept { return m_num_channels; }
	uint32_t sample_rate() const noexcept { return m_sample_rate; }
	uint32_t bits_per_sample() const noexcept { return m_bits_per_sample; }

	void set_data(uint8_t* data) noexcept { m_data = data; }
	void set_size(size_t size) noexcept { m_size = size; }
	void set_num_channels(uint32_t num_channels) noexcept { m_num_channels = num_channels; }
	void set_sample_rate(uint32_t sample_rate) noexcept { m_sample_rate = sample_rate; }
	void set_bits_per_sample(uint32_t bits_per_sample) noexcept { m_bits_per_sample = bits_per_sample; }

	void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOUND_DATA_H__
