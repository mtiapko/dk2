#ifndef __DK_GL_WINDOW_H__
#define __DK_GL_WINDOW_H__

#include <EGL/egl.h>
#undef Status //  XXX: Xlib...

#include "dk/graph/Window.h"
#include "Common.h"

namespace gl
{

class Window final : public graph::Window
{
private:
	static inline EGLDisplay s_egl_display = nullptr;

	EGLConfig  m_config  = nullptr;
	EGLContext m_context = EGL_NO_CONTEXT;
	EGLSurface m_surface = EGL_NO_SURFACE;
	::Window   m_window  = None;

public:
	Window(class Renderer* renderer) noexcept { this->set_resource_creator((sys::ResourceCreator*)renderer); }
	~Window() noexcept override { this->destroy(); }

	void render() noexcept override;

	void enable() noexcept override;
	void disable() noexcept override;

	Status create(const graph::WindowData& data /* = {} */) noexcept override;
	void destroy() noexcept override;
};

}

#endif // !__DK_GL_WINDOW_H__
