#include "dk/sys/events/MouseMoveEvent.h"
#include "dk/sys/events/MousePressEvent.h"
#include "dk/sys/events/MouseReleaseEvent.h"
#include "dk/sys/EventManager.h"
#include "dk/sys/Mouse.h"
#include "dk/os/Descriptor.h"
#include "dk/Assert.h"

namespace dk::sys
{

/* static */ Mouse Mouse::s_this;

/* static */ bool Mouse::s_state[(int)MouseBtn::ENUM_SIZE];
/* static */ int  Mouse::s_x;
/* static */ int  Mouse::s_y;
/* static */ int  Mouse::s_dx;
/* static */ int  Mouse::s_dy;

/* static */ void Mouse::record_input(bool val) noexcept
{
	//  TODO: maybe read mouse pos and write to x and y?
	if (val) {
		EventManager<MouseMoveEvent>::get().subscribe(&s_this);
		EventManager<MousePressEvent>::get().subscribe(&s_this);
		EventManager<MouseReleaseEvent>::get().subscribe(&s_this);
	} else {
		//  TODO: remove
	}
}

/* static */ void Mouse::set_position(int x, int y) noexcept
{
	static auto dpy = os::Descriptor::get();
	auto root_window = XRootWindow(dpy, 0);
	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);
}

void Mouse::handle(const MouseMoveEvent& e) noexcept /* override */
{
	s_dx += e.x() - s_x;
	s_dy += e.y() - s_y;

	s_x = e.x();
	s_y = e.y();
}

void Mouse::handle(const MousePressEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < MouseBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = true;
}

void Mouse::handle(const MouseReleaseEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < MouseBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
