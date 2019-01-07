#include "audio/debug.h"

#define CASE_CODE(code) case code: return string_view(#code)

namespace dk::audio
{

/* static */ string_view debug::code_to_str(ALenum code) noexcept
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
	return string_view("AL_UNKNOWN_ERROR");
}

}
