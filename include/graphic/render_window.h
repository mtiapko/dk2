#ifndef __DK_RENDER_WINDOW_H__
#define __DK_RENDER_WINDOW_H__

#include <EGL/egl.h>
#include "ret_code.h"

namespace dk
{

class render_window
{
private:
	Display*   m_display;
	EGLDisplay m_egl_display;
	EGLConfig  m_config;
	EGLContext m_context;
	EGLSurface m_surface;
	Window     m_window;

public:
	void render() const { eglSwapBuffers(m_egl_display, m_surface); }

	ret_code create();
};

}

#endif  //  !__DK_RENDER_WINDOW_H__
