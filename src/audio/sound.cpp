#include "audio/debug.h"
#include "audio/sound.h"

namespace dk::audio
{

sound::sound() noexcept
	: m_id(0)
{}

sound::~sound() noexcept /* override */
{
	this->destroy();
}

/* static */ ALenum sound::convert_to_al_fmt(uint32_t num_channels, uint32_t bits_per_sample) noexcept
{
	switch (bits_per_sample) {
		case 8:
			if (num_channels == 1) return AL_FORMAT_MONO8;
			else if (num_channels == 2) return AL_FORMAT_STEREO8;

			DK_LOG_ERROR("Unsupported sound channels count: ", num_channels);
			return 0;
		case 16:
			if (num_channels == 1) return AL_FORMAT_MONO16;
			else if (num_channels == 2) return AL_FORMAT_STEREO16;

			DK_LOG_ERROR("Unsupported sound channels count: ", num_channels);
			return 0;
	}

	DK_LOG_ERROR("Unsupported sound bits ber sample count: ", bits_per_sample);
	return 0;
}

status sound::create(string_view file_path, sound_data_fmt fmt /* = sound_data_fmt::AUTO */) noexcept
{
	sound_data data;
	if (auto ret = data.create(file_path, fmt); !ret)
		return ret;

	return this->create(data);
}

status sound::create(const sound_data& data) noexcept
{
	AL_CALL(alGenBuffers(1, &m_id));
	AL_CALL(alBufferData(m_id, convert_to_al_fmt(data.num_channels(), data.bits_per_sample()), data.data(), data.size(), data.sample_rate()));
	return status::OK;
}

void sound::destroy() noexcept
{
	if (m_id != 0) {
		AL_CALL(alDeleteBuffers(1, &m_id));
		m_id = 0;
	}
}

}
