#include "log.h"
#include "graphic/render_system.h"

namespace dk
{

render_system::render_system()
	: m_display(nullptr)
{}

ret_code render_system::create()
{
	if (m_display != nullptr)
		return ret_code::OK;

	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (m_display == nullptr) {
		DK_LOG_ERROR("Failed to get display");
		return ret_code::ERORR;
	}

	EGLint egl_major_ver;
	EGLint egl_minor_ver;
	if (eglInitialize(m_display, &egl_major_ver, &egl_minor_ver) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to initialize EGL");
		return ret_code::ERORR;
	}

	DK_LOG_OK("EGL v", egl_major_ver, '.', egl_minor_ver, " successfully initialized");
	return ret_code::OK;
}

}
