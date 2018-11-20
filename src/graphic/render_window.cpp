#include "log.h"
#include "core.h"
#include "graphic/render_window.h"

namespace dk
{

ret_code render_window::create()
{
	auto render_sys = core::get_render_sys();
	Display* display = render_sys->get_display();
	EGLDisplay egl_display = render_sys->get_egl_display();

	static EGLint const attrib_list[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		//EGL_BUFFER_SIZE,     32,
		//EGL_RED_SIZE,        8,
		//EGL_GREEN_SIZE,      8,
		//EGL_BLUE_SIZE,       8,
		//EGL_ALPHA_SIZE,      8,
		//EGL_SAMPLES,         4,
		EGL_NONE
	};

	EGLint config_count;
	if (eglChooseConfig(egl_display, attrib_list, &m_config, 1, &config_count) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to choose EGL config");
		return ret_code::ERORR;
	}

	if (config_count == 0) {
		DK_LOG_ERROR("No matching EGL configs found");
		return ret_code::ERORR;
	}

	m_context = eglCreateContext(egl_display, m_config, EGL_NO_CONTEXT, nullptr);
	if (m_context == EGL_NO_CONTEXT) {
		DK_LOG_ERROR("Failed to create EGL context");
		return ret_code::ERORR;
	}

	EGLint vi_id;
	if (eglGetConfigAttrib(egl_display, m_config, EGL_NATIVE_VISUAL_ID, &vi_id) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to get visual info ID from EGL");
		return ret_code::ERORR;
	}

	int vi_count;
	XVisualInfo vi_tmpl { .visualid = (VisualID)vi_id, .screen = DefaultScreen(display) };
	XVisualInfo* vi = XGetVisualInfo(display, VisualIDMask | VisualScreenMask, &vi_tmpl, &vi_count);
	if (vi == nullptr || vi_count == 0) {
		DK_LOG_ERROR("Failed to get visual info");
		return ret_code::ERORR;
	}

	m_window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, 800, 600, 0,
		vi->depth, InputOutput, vi->visual, 0, nullptr);
	XFree(vi);

	if (m_window == 0) {
		DK_LOG_ERROR("Failed to create window");
		return ret_code::ERORR;
	}

	DK_LOG_OK("Window successfully create");
	XStoreName(display, m_window, "tst | v0.0.1");
	XMapWindow(display, m_window);

	m_surface = eglCreateWindowSurface(egl_display, m_config, m_window, nullptr);
	if (m_surface == nullptr) {
		DK_LOG_ERROR("Failed to create window surface");
		return ret_code::ERORR;
	}

	eglMakeCurrent(egl_display, m_surface, m_surface, m_context);
	DK_LOG_OK("OpenGL context successfully created");
	return ret_code::OK;
}

}
