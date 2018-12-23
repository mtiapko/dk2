#ifndef __DK_SYS_RENDERER_WINDOW_H__
#define __DK_SYS_RENDERER_WINDOW_H__

#include <EGL/egl.h>
#include "status.h"

namespace dk::sys
{

class renderer_window
{
private:
	Display*   m_display;
	EGLDisplay m_egl_display;
	EGLConfig  m_config;
	EGLContext m_context;
	EGLSurface m_surface;
	Window     m_window;

public:
	void render() const noexcept;

	status create() noexcept;
};

}

#endif  //  !__DK_SYS_RENDERER_WINDOW_H__
