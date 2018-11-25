#ifndef __DK_GL_H__
#define __DK_GL_H__

#include <GL/glew.h>

#define GL_CALL(call) \
	call, \
	[&]() { if (auto err = glGetError(); err != GL_NO_ERROR) \
		dk::gl_print_error(__FILE__, __func__, __LINE__, err, #call); }()

namespace dk
{

void gl_print_error(const char* file, const char* func, int line, int err, const char* call);

}

#endif  //  !__DK_GL_H__
