#ifndef __DK_GL_DEBUG_H__
#define __DK_GL_DEBUG_H__

#include <GL/gl.h>
#include "dk/containers/StringView.h"
#include "dk/Log.h"
#include "Common.h"

#define GL_CALL_CHECK(func) \
	[](StringView func_name) noexcept { \
		if(auto err = glGetError(); err != GL_NO_ERROR) \
			DK_LOG_ERROR_IMPL(__FILE__, func_name, __LINE__, \
				"OpenGL function '", #func, "' failed: ", Debug::code_to_str(err)); \
	}(__func__)

#define GL_CALL(func)     func, GL_CALL_CHECK(func)
#define GL_CALL_RET(func) func; GL_CALL_CHECK(func)

namespace gl
{

class Debug
{
public:
	static StringView code_to_str(GLenum code) noexcept;
};

}

#endif // !__DK_GL_DEBUG_H__
