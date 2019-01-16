#include "graph/Debug.h"

#define CASE_CODE(code) case code: return StringView(#code)

namespace dk::graph
{

/* static */ StringView Debug::code_to_str(GLenum code) noexcept
{
	switch (code) {
		CASE_CODE(GL_NO_ERROR);
		CASE_CODE(GL_INVALID_ENUM);
		CASE_CODE(GL_INVALID_VALUE);
		CASE_CODE(GL_INVALID_OPERATION);
		CASE_CODE(GL_STACK_OVERFLOW);
		CASE_CODE(GL_STACK_UNDERFLOW);
		CASE_CODE(GL_TABLE_TOO_LARGE);
		CASE_CODE(GL_INVALID_FRAMEBUFFER_OPERATION);
		CASE_CODE(GL_OUT_OF_MEMORY);
	}

	DK_LOG_WARNING("OpenGL unknown error code #", code);
	return StringView("GL_UNKNOWN_ERROR");
}

}
