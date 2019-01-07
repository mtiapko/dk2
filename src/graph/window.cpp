#include <GL/gl.h>
#include "log.h"
#include "core.h"
#include "graph/window.h"

namespace dk::graph
{

/* static */ Display*   window::s_display;
/* static */ EGLDisplay window::s_egl_display;

void window::render() const noexcept
{
	eglSwapBuffers(s_egl_display, m_surface);
}

/* static */ Display* window::display() noexcept
{
	return s_display;
}

status window::create() noexcept
{
	if (s_display == nullptr) {
		s_display = XOpenDisplay(nullptr);
		if (s_display == nullptr) {
			DK_LOG_ERROR("Failed to open display connection");
			return status::ERROR;
		}
	}

	if (s_egl_display == nullptr) {
		s_egl_display = eglGetDisplay(s_display);
		if (s_egl_display == nullptr) {
			DK_LOG_ERROR("Failed to get EGL display");
			return status::ERROR;
		}

		EGLint egl_major_ver;
		EGLint egl_minor_ver;
		if (eglInitialize(s_egl_display, &egl_major_ver, &egl_minor_ver) != EGL_TRUE) {
			DK_LOG_ERROR("Failed to initialize EGL");
			return status::ERROR;
		}

		DK_LOG_OK("EGL v", egl_major_ver, '.', egl_minor_ver, " initialized");
	}

	static EGLint const config_attrib_list[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_DEPTH_SIZE,      24,
		EGL_BUFFER_SIZE,     32,
		//EGL_RED_SIZE,        8,
		//EGL_GREEN_SIZE,      8,
		//EGL_BLUE_SIZE,       8,
		//EGL_ALPHA_SIZE,      8,
		//EGL_SAMPLES,         8,
		EGL_NONE
	};

	EGLint configs_count;
	if (eglChooseConfig(s_egl_display, config_attrib_list, &m_config, 1, &configs_count) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to choose EGL config");
		return status::ERROR;
	}

	if (configs_count == 0) {
		DK_LOG_ERROR("No matching EGL configs found");
		return status::ERROR;
	}

	EGLint vi_id;
	if (eglGetConfigAttrib(s_egl_display, m_config, EGL_NATIVE_VISUAL_ID, &vi_id) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to get visual info ID from EGL");
		return status::ERROR;
	}

	int vi_count;
	XVisualInfo vi_tmpl { .visualid = (VisualID)vi_id, .screen = DefaultScreen(s_display) };
	XVisualInfo* vi = XGetVisualInfo(s_display, VisualIDMask | VisualScreenMask, &vi_tmpl, &vi_count);
	if (vi == nullptr || vi_count == 0) {
		DK_LOG_ERROR("Failed to get visual info");
		return status::ERROR;
	}

	m_window = XCreateWindow(s_display, RootWindow(s_display, vi->screen),
		0, 0, 800, 600, 0, vi->depth, InputOutput, vi->visual, 0, nullptr);
	XFree(vi);

	if (m_window == 0) {
		DK_LOG_ERROR("Failed to create window");
		return status::ERROR;
	}

	DK_LOG_OK("Window created");
	XStoreName(s_display, m_window, "tst | v0.0.1");
	XSetIconName(s_display, m_window, "(icon) tst | v0.0.1");
	XSelectInput(s_display, m_window, KeyPressMask | KeyReleaseMask
		| PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(s_display, m_window);

	if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
		DK_LOG_ERROR("EGL failed to bind OpenGL API");
		return status::ERROR;
	}

	m_surface = eglCreateWindowSurface(s_egl_display, m_config, m_window, nullptr);
	if (m_surface == nullptr) {
		DK_LOG_ERROR("Failed to create window surface");
		return status::ERROR;
	}

	static EGLint const context_attrib_list[] = {
		EGL_CONTEXT_MAJOR_VERSION, 3,
		EGL_CONTEXT_MINOR_VERSION, 3,
		EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
		EGL_NONE
	};

	m_context = eglCreateContext(s_egl_display, m_config, EGL_NO_CONTEXT, context_attrib_list);
	if (m_context == EGL_NO_CONTEXT) {
		DK_LOG_ERROR("Failed to create OpenGL context");
		return status::ERROR;
	}

	eglMakeCurrent(s_egl_display, m_surface, m_surface, m_context);

	auto glsl_ver = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	DK_LOG_OK(
		"OpenGL context created:\n"
		"\tvendor:       ", glGetString(GL_VENDOR), '\n',
		"\trenderer:     ", glGetString(GL_RENDERER), '\n',
		"\tversion:      ", glGetString(GL_VERSION), '\n',
		"\tGLSL version: ", (glsl_ver != nullptr ? glsl_ver : "(none)"));

	auto renderer = core::active<graph::renderer>();
	if (renderer->create() != status::OK)
		return status::ERROR;

	return status::OK;
}

}
