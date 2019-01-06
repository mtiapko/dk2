#include "audio/debug.h"
#include "audio/source.h"

namespace dk::audio
{

source::source() noexcept
	: m_id(0)
{}

source::~source() noexcept
{
	if (m_id != 0)
		AL_CALL(alDeleteSources(1, &m_id));
}

void source::play() const noexcept
{
	AL_CALL(alSourcePlay(m_id));
}

void source::pause() const noexcept
{
	AL_CALL(alSourcePause(m_id));
}

void source::stop() const noexcept
{
	AL_CALL(alSourceStop(m_id));
}

void source::set_sound(const sound& snd) const noexcept
{
	AL_CALL(alSourcei(m_id, AL_BUFFER, snd.id()));
}

void source::set_pitch(float val) const noexcept
{
	AL_CALL(alSourcef(m_id, AL_PITCH, val));
}

void source::set_gain(float val) const noexcept
{
	AL_CALL(alSourcef(m_id, AL_GAIN, val));
}

void source::set_pos(float x, float y, float z) const noexcept
{
	AL_CALL(alSource3f(m_id, AL_POSITION, x, y, z));
}

void source::set_vel(float x, float y, float z) const noexcept
{
	AL_CALL(alSource3f(m_id, AL_VELOCITY, x, y, z));
}

void source::set_loop(bool val) const noexcept
{
	AL_CALL(alSourcei(m_id, AL_LOOPING, val));
}

status source::create() noexcept
{
	AL_CALL(alGenSources(1, &m_id));
	this->set_pitch(1.0f);
	this->set_gain(1.0f);
	this->set_pos(0.0f, 0.0f, 0.0f);
	this->set_vel(0.0f, 0.0f, 0.0f);
	this->set_loop(false);

	return status::OK;
}

}
