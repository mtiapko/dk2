#include "log.h"
#include "graphic/gl.h"
#include "containers/string_view.h"

namespace dk
{

void gl_print_error(const char* file, const char* func, int line, int err, const char* call)
{
	auto get_gl_error_name = [](auto err) -> string_view {
		switch (err) {
			case GL_NO_ERROR:                      return "GL_NO_ERROR";
			case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
			case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
			case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
			case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
			case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
			default:                               return "GL_UNKNOWN_ERROR";
		};
	};

	DK_LOG_ERROR_IMPL(file, func, line, "OpenGL error ", get_gl_error_name(err), " (", err, "): ", call);
}

}
