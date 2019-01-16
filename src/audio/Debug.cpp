#include "audio/Debug.h"

#define CASE_CODE(code) case code: return StringView(#code)

namespace dk::audio
{

/* static */ StringView Debug::code_to_str(ALenum code) noexcept
{
	switch (code) {
		CASE_CODE(AL_NO_ERROR);
		CASE_CODE(AL_INVALID_NAME);
		CASE_CODE(AL_INVALID_ENUM);
		CASE_CODE(AL_INVALID_VALUE);
		CASE_CODE(AL_INVALID_OPERATION);
		CASE_CODE(AL_OUT_OF_MEMORY);
	}

	DK_LOG_WARNING("OpenAL unknown error code #", code);
	return StringView("AL_UNKNOWN_ERROR");
}

}
