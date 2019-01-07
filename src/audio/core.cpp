#include "audio/debug.h"
#include "audio/core.h"

namespace dk::audio
{

/* static */ ALCdevice* core::s_device;
/* static */ ALCcontext* core::s_context;

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

	return status::OK;
}

}
