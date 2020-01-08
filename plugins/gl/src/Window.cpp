#include <thread>
#include "Renderer.h"         /* XXX: #include <EGL/egl.h> */
#include <EGL/eglext.h>       /* XXX: must be after EGL include */
#include "dk/os/Descriptor.h" /* XXX: must after EGL include to #undef Status */
#include "Debug.h"

namespace gl
{

void Window::render() noexcept /* override */
{
	eglSwapBuffers(s_egl_display, m_surface);
}

void Window::enable() noexcept /* override */
{
	eglMakeCurrent(s_egl_display, m_surface, m_surface, m_context);
}

void Window::disable() noexcept /* override */
{
	eglMakeCurrent(s_egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

Status Window::create(const graph::WindowData& data /* = {} */) noexcept /* override */
{
	auto dpy = os::Descriptor::get();
	if (s_egl_display == nullptr) {
		s_egl_display = eglGetDisplay(dpy);
		if (s_egl_display == nullptr) {
			DK_LOG_ERROR("Failed to get EGL display");
			return Status::ERROR;
		}

		EGLint egl_major_ver;
		EGLint egl_minor_ver;
		if (eglInitialize(s_egl_display, &egl_major_ver, &egl_minor_ver) != EGL_TRUE) {
			DK_LOG_ERROR("Failed to initialize EGL");
			return Status::ERROR;
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
		//EGL_SAMPLES,         2,
		EGL_NONE
	};

	EGLint configs_count;
	if (eglChooseConfig(s_egl_display, config_attrib_list, &m_config, 1, &configs_count) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to choose EGL config");
		return Status::ERROR;
	}

	if (configs_count == 0) {
		DK_LOG_ERROR("No matching EGL configs found");
		return Status::ERROR;
	}

	EGLint vi_id;
	if (eglGetConfigAttrib(s_egl_display, m_config, EGL_NATIVE_VISUAL_ID, &vi_id) != EGL_TRUE) {
		DK_LOG_ERROR("Failed to get visual info ID from EGL");
		return Status::ERROR;
	}

	XVisualInfo vi_tmpl;
	vi_tmpl.visualid = (VisualID)vi_id;
	vi_tmpl.screen = DefaultScreen(dpy);

	int vi_count;
	XVisualInfo* vi = XGetVisualInfo(dpy, VisualIDMask | VisualScreenMask, &vi_tmpl, &vi_count);
	if (vi == nullptr || vi_count == 0) {
		DK_LOG_ERROR("Failed to get visual info");
		return Status::ERROR;
	}

	// TODO: data.x & data.y center
	m_window = XCreateWindow(dpy, RootWindow(dpy, vi->screen),
		data.x, data.y, data.width, data.height, 0, vi->depth, InputOutput, vi->visual, 0, nullptr);
	XFree(vi);

	if (m_window == 0) {
		DK_LOG_ERROR("Failed to create window");
		return Status::ERROR;
	}

	/* enable window close event */
	Atom delete_msg = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(dpy, m_window, &delete_msg, 1);

	XStoreName(dpy, m_window, data.title.data());
	XSetIconName(dpy, m_window, "(icon test)");  //  TODO: no action? remove!
	XSelectInput(dpy, m_window, KeyPressMask | KeyReleaseMask
		| PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(dpy, m_window);

	auto create_null_cursor = [](Display* dpy, Drawable dw) noexcept {
		XColor color = {};
		const char data[] = { 0 };

		Pixmap pixmap = XCreateBitmapFromData(dpy, dw, data, 1, 1);
		Cursor cursor = XCreatePixmapCursor(dpy, pixmap, pixmap, &color, &color, 0, 0);

		XFreePixmap(dpy, pixmap);

		return cursor;
	};

	auto null_cursor = create_null_cursor(dpy, m_window);
	while (false) { // TODO: move to mouse
		auto grab_status = XGrabPointer(dpy, m_window, True, PointerMotionMask,
			GrabModeAsync, GrabModeAsync, m_window, null_cursor, CurrentTime);

		if (grab_status == GrabSuccess)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
		DK_LOG_ERROR("EGL failed to bind OpenGL API");
		return Status::ERROR;
	}

	m_surface = eglCreateWindowSurface(s_egl_display, m_config, m_window, nullptr);
	if (m_surface == nullptr) {
		DK_LOG_ERROR("Failed to create window surface");
		return Status::ERROR;
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
		return Status::ERROR;
	}

	/* activate context */
	this->enable();
	eglSwapInterval(s_egl_display, data.v_sync);

	auto glsl_ver = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	DK_LOG_OK(
		"OpenGL context created:\n"
		"\tvendor:       ", glGetString(GL_VENDOR), '\n',
		"\trenderer:     ", glGetString(GL_RENDERER), '\n',
		"\tversion:      ", glGetString(GL_VERSION), '\n',
		"\tGLSL version: ", (glsl_ver != nullptr ? glsl_ver : "(none)")
	);

	if (((Renderer*)this->resource_creator())->create() != Status::OK)
		return Status::ERROR;

	DK_LOG_OK("Graphic window created");
	return Status::OK;
}

void Window::destroy() noexcept /* override */
{
	// TODO: destroy
	this->disable();
}

}
