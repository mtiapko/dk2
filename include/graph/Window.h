#ifndef __DK_GRAPH_WINDOW_H__
#define __DK_GRAPH_WINDOW_H__

#include <EGL/egl.h>

//  XXX: Xlib...
#undef Status

#include "Status.h"

namespace dk::graph
{

class Window
{
private:
	static Display*   s_display;
	static EGLDisplay s_egl_display;

	EGLConfig  m_config;
	EGLContext m_context;
	EGLSurface m_surface;
	::Window   m_window;

	uint32_t m_width;
	uint32_t m_height;

public:
	Window() noexcept;

	void clear() const noexcept;
	void render() const noexcept;  //  TODO: inherit from render_target or render_buffer

	uint32_t width() const noexcept { return m_width; }
	uint32_t height() const noexcept { return m_height; }
	float    ratio() const noexcept { return (float)m_width / m_height; }

	static Display* display() noexcept;

	Status create() noexcept;
};

}

#endif  //  !__DK_GRAPH_WINDOW_H__
