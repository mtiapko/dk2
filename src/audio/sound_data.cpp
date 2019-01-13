#include "audio/sound_data.h"
#include "fs/file.h"
#include "log.h"
#include "mem.h"

namespace dk::audio
{

sound_data::sound_data() noexcept
	: m_data(nullptr)
	, m_size(0)
	, m_num_channels(0)
	, m_sample_rate(0)
	, m_bits_per_sample(0)
{}

sound_data::~sound_data() noexcept /* override */
{
	this->destroy();
}

void sound_data::destroy() noexcept
{
	if (m_data != nullptr) {
		mem_destroy(m_data);
		m_data = nullptr;
	}
}

}
