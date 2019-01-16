#include "audio/Debug.h"
#include "audio/Source.h"

namespace dk::audio
{

Source::Source() noexcept
	: m_id(0)
{}

Source::~Source() noexcept
{
	this->destroy();
}

void Source::play() const noexcept
{
	AL_CALL(alSourcePlay(m_id));
}

void Source::pause() const noexcept
{
	AL_CALL(alSourcePause(m_id));
}

void Source::rewind() const noexcept
{
	AL_CALL(alSourceRewind(m_id));
	this->play();
}

void Source::stop() const noexcept
{
	AL_CALL(alSourceStop(m_id));
}

float Source::sec_offset() const noexcept
{
	float val;
	AL_CALL(alGetSourcef(m_id, AL_SEC_OFFSET, &val));
	return val;
}

int32_t Source::byte_offset() const noexcept
{
	int32_t val;
	AL_CALL(alGetSourcei(m_id, AL_BYTE_OFFSET, &val));
	return val;
}

void Source::set_sec_offset(float val) const noexcept
{
	AL_CALL(alSourcef(m_id, AL_SEC_OFFSET, val));
}

void Source::set_byte_offset(int32_t val) const noexcept
{
	AL_CALL(alSourcei(m_id, AL_BYTE_OFFSET, val));
}

void Source::set(const Sound& snd) const noexcept
{
	AL_CALL(alSourcei(m_id, AL_BUFFER, snd.id()));
}

void Source::remove_sound() const noexcept
{
	this->stop();
	AL_CALL(alSourcei(m_id, AL_BUFFER, 0));
}

void Source::set_pitch(float val) const noexcept
{
	AL_CALL(alSourcef(m_id, AL_PITCH, val));
}

void Source::set_gain(float val) const noexcept
{
	AL_CALL(alSourcef(m_id, AL_GAIN, val));
}

void Source::set_pos(math::Vec3f val) const noexcept
{
	AL_CALL(alSource3f(m_id, AL_POSITION, val.x, val.y, val.z));
}

void Source::set_dir(math::Vec3f val) const noexcept
{
	AL_CALL(alSource3f(m_id, AL_DIRECTION, val.x, val.y, val.z));
}

void Source::set_velocity(math::Vec3f val) const noexcept
{
	AL_CALL(alSource3f(m_id, AL_VELOCITY, val.x, val.y, val.z));
}

void Source::set_looping(bool val) const noexcept
{
	AL_CALL(alSourcei(m_id, AL_LOOPING, val));
}

float Source::pitch() const noexcept
{
	float val;
	AL_CALL(alGetSourcef(m_id, AL_PITCH, &val));
	return val;
}

float Source::gain() const noexcept
{
	float val;
	AL_CALL(alGetSourcef(m_id, AL_GAIN, &val));
	return val;
}

math::Vec3f Source::pos() const noexcept
{
	math::Vec3f val;
	AL_CALL(alGetSource3f(m_id, AL_POSITION, &val.x, &val.y, &val.z));
	return val;
}

math::Vec3f Source::dir() const noexcept
{
	math::Vec3f val;
	AL_CALL(alGetSource3f(m_id, AL_DIRECTION, &val.x, &val.y, &val.z));
	return val;
}

math::Vec3f Source::velocity() const noexcept
{
	math::Vec3f val;
	AL_CALL(alGetSource3f(m_id, AL_VELOCITY, &val.x, &val.y, &val.z));
	return val;
}

bool Source::looping() const noexcept
{
	int val;
	AL_CALL(alGetSourcei(m_id, AL_LOOPING, &val));
	return val;
}

Status Source::create() noexcept
{
	AL_CALL(alGenSources(1, &m_id));
	this->set_pitch(1.0f);
	this->set_gain(1.0f);
	this->set_pos({ 0.0f, 0.0f, -1.0f });
	this->set_dir({ 0.0f, 0.0f, 0.0f });
	this->set_velocity({ 0.0f, 0.0f, 0.0f });
	this->set_looping(false);

	return Status::OK;
}

void Source::destroy() noexcept
{
	if (m_id != 0) {
		AL_CALL(alDeleteSources(1, &m_id));
		m_id = 0;
	}
}

}
