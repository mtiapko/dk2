#ifndef __DK_GRAPH_DEBUG_H__
#define __DK_GRAPH_DEBUG_H__

#include <GL/gl.h>
#include "containers/StringView.h"
#include "Log.h"

#define GL_CALL(func) \
	func, \
	[](StringView func_name) { \
		if(auto err = glGetError(); err != GL_NO_ERROR) \
			DK_LOG_ERROR_IMPL(__FILE__, func_name, __LINE__, \
				"OpenGL function '", #func, "' failed: ", Debug::code_to_str(err)); \
	}(__func__)

namespace dk::graph
{

class Debug
{
public:
	static StringView code_to_str(GLenum code) noexcept;
};

}

#endif  //  !__DK_AUDIO_DEBUG_H__
