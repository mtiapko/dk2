#include "audio/debug.h"
#include "audio/core.h"

namespace dk::audio
{

ALCdevice* core::s_device;
ALCcontext* core::s_context;

/* static */ status core::create() noexcept
{
	ALCdevice* s_device = alcOpenDevice(nullptr);
	if (s_device == nullptr)
		return status::ERROR;

	const ALCint context_attr[] = {
		ALC_FREQUENCY,      0,
		ALC_MONO_SOURCES,   0,
		ALC_REFRESH,        0,
		ALC_STEREO_SOURCES, 0,
		ALC_SYNC,           0,
		0
	};

	ALCcontext* s_context = alcCreateContext(s_device, context_attr);
	if (s_context == nullptr)
		return status::ERROR;

	if (alcMakeContextCurrent(s_context) != ALC_TRUE)
		return status::ERROR;

	ALfloat orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
	AL_CALL(alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f));
	AL_CALL(alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f));
	AL_CALL(alListenerfv(AL_ORIENTATION, orientation));
	return status::OK;
}

}
