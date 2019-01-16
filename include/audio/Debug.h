#ifndef __DK_AUDIO_DEBUG_H__
#define __DK_AUDIO_DEBUG_H__

#include <AL/al.h>
#include "containers/StringView.h"
#include "Log.h"

#define AL_CALL(func) \
	func, \
	[](StringView func_name) { \
		if(auto err = alGetError(); err != AL_NO_ERROR) \
			DK_LOG_ERROR_IMPL(__FILE__, func_name, __LINE__, \
				"OpenAL function '", #func, "' failed: ", Debug::code_to_str(err)); \
	}(__func__)

namespace dk::audio
{

class Debug
{
public:
	static StringView code_to_str(ALenum code) noexcept;
};

}

#endif  //  !__DK_AUDIO_DEBUG_H__
