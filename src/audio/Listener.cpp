#include "audio/Debug.h"
#include "audio/Listener.h"

namespace dk::audio
{

/* static */ void Listener::set_gain(float val) noexcept
{
	AL_CALL(alListenerf(AL_GAIN, val));
}

/* static */ void Listener::set_pos(math::Vec3f val) noexcept
{
	AL_CALL(alListener3f(AL_POSITION, val.x, val.y, val.z));
}

/* static */ void Listener::set_velocity(math::Vec3f val) noexcept
{
	AL_CALL(alListener3f(AL_VELOCITY, val.x, val.y, val.z));
}

/* static */ void Listener::set_orientation(math::Vec3f dir, math::Vec3f up) noexcept
{
	const float orientation[] = { dir.x, dir.y, dir.z, up.x, up.y, up.z };
	AL_CALL(alListenerfv(AL_ORIENTATION, orientation));
}

/* static */ void Listener::set_orientation(const float orientation[]) noexcept
{
	AL_CALL(alListenerfv(AL_ORIENTATION, orientation));
}

/* static */ Status Listener::create() noexcept
{
	static constexpr float orientation[] = { /* dir */ 0.0f, 0.0f, -1.0f, /* up */ 0.0f, 1.0f, 0.0f };

	set_pos({ 0.0f, 0.0f, 0.0f });
	set_velocity({ 0.0f, 0.0f, 0.0f });
	set_orientation(orientation);
	return Status::OK;
}

}
