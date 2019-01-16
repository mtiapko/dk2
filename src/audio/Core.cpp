#include "audio/Debug.h"
#include "audio/Core.h"

namespace dk::audio
{

/* static */ ALCdevice*  Core::s_device;
/* static */ ALCcontext* Core::s_context;

/* static */ Status Core::create() noexcept
{
	s_device = alcOpenDevice(nullptr);
	if (s_device == nullptr) {
		DK_LOG_ERROR("OpenAL failed to open device");
		return Status::ERROR;
	}

	const ALCint context_attr[] = {
		ALC_FREQUENCY,      0,
		ALC_MONO_SOURCES,   0,
		ALC_REFRESH,        0,
		ALC_STEREO_SOURCES, 0,
		ALC_SYNC,           0,
		0
	};

	s_context = alcCreateContext(s_device, context_attr);
	if (s_context == nullptr) {
		DK_LOG_ERROR("OpenAL failed to create context");
		return Status::ERROR;
	}

	if (alcMakeContextCurrent(s_context) != ALC_TRUE) {
		DK_LOG_ERROR("OpenAL failed to make context current");
		return Status::ERROR;
	}

	if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT") == AL_TRUE) {
		DK_LOG_OK(
			"Audio Core created:\n",
			"\tdevice:  ", alcGetString(s_device, ALC_DEVICE_SPECIFIER), '\n',
			"\tcapture: ", alcGetString(s_device, ALC_CAPTURE_DEVICE_SPECIFIER), '\n',
			"\tvendor:  ", alGetString(AL_VENDOR), '\n',
			"\tversion: ", alGetString(AL_VERSION)
		);
	} else {
		DK_LOG_OK("Audio Core created with unknown default device");
	}

	return Status::OK;
}

/* static */ void Core::destroy() noexcept
{
	if (s_device == nullptr)
		return;

	if (s_context != nullptr) {
		if (alcMakeContextCurrent(nullptr) != ALC_TRUE)
			DK_LOG_ERROR("OpenAL failed to deactivate context");

		alcDestroyContext(s_context);
		if (alcGetError(s_device) != ALC_NO_ERROR)
			DK_LOG_ERROR("OpenAL failed to destroy context");

		s_context = nullptr;
	}

	if (alcCloseDevice(s_device) != ALC_TRUE)
		DK_LOG_ERROR("Failed to close audio device. Note: remove all contexts and buffers");

	s_device = nullptr;
	DK_LOG_OK("Audio Core destroyed");
}

}
