#ifndef __DK_RENDER_SYSTEM_H__
#define __DK_RENDER_SYSTEM_H__

#include <EGL/egl.h>
#include "ret_code.h"

namespace dk
{

class render_system
{
private:
	Display*   m_display;
	EGLDisplay m_egl_display;

public:
	render_system();

	Display* get_display() { return m_display; }
	EGLDisplay get_egl_display() { return m_egl_display; }

	ret_code create();
};

}

#endif  //  !__DK_RENDER_SYSTEM_H__
