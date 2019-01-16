#include "sys/events/MouseMoveEvent.h"
#include "sys/events/MousePressEvent.h"
#include "sys/events/MouseReleaseEvent.h"
#include "sys/EventManager.h"
#include "sys/Mouse.h"
#include "Assert.h"

namespace dk::sys
{

/* static */ Mouse Mouse::s_this;

/* static */ bool Mouse::s_state[(int)MouseBtn::ENUM_SIZE];
/* static */ int  Mouse::s_x;
/* static */ int  Mouse::s_y;

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

void Mouse::handle(const MouseMoveEvent& e) noexcept /* override */
{
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
