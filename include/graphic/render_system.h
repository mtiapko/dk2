#ifndef __DK_RENDER_SYSTEM_H__
#define __DK_RENDER_SYSTEM_H__

#include <EGL/egl.h>
#include "ret_code.h"

namespace dk
{

class render_system
{
private:
	EGLDisplay m_display;
	EGLConfig  m_config;

public:
	render_system();

	ret_code create();
};

}

#endif  //  !__DK_RENDER_SYSTEM_H__
