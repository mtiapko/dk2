#include "audio/SoundData.h"
#include "Mem.h"

namespace dk::audio
{

SoundData::SoundData() noexcept
	: m_data(nullptr)
	, m_size(0)
	, m_num_channels(0)
	, m_sample_rate(0)
	, m_bits_per_sample(0)
{}

SoundData::~SoundData() noexcept /* override */
{
	this->destroy();
}

void SoundData::destroy() noexcept
{
	if (m_data != nullptr) {
		mem_dealloc(m_data);
		m_data = nullptr;
	}
}

}
