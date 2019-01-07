#include "sys/events/mouse_move_event.h"
#include "sys/events/mouse_press_event.h"
#include "sys/events/mouse_release_event.h"
#include "sys/event_manager.h"
#include "sys/mouse.h"
#include "assert.h"

namespace dk::sys
{

/* static */ mouse mouse::s_this;

/* static */ bool mouse::s_state[(int)mouse_btn::ENUM_SIZE];
/* static */ int  mouse::s_x;
/* static */ int  mouse::s_y;

/* static */ void mouse::record_input(bool val) noexcept
{
	//  TODO: maybe read mouse pos and write to x and y?
	if (val) {
		event_manager<mouse_move_event>::get().subscribe(&s_this);
		event_manager<mouse_press_event>::get().subscribe(&s_this);
		event_manager<mouse_release_event>::get().subscribe(&s_this);
	} else {
		//  TODO: remove
	}
}

void mouse::handle(const mouse_move_event& e) noexcept /* override */
{
	s_x = e.x();
	s_y = e.y();
}

void mouse::handle(const mouse_press_event& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < mouse_btn::ENUM_SIZE);
	s_state[(int)e.btn()] = true;
}

void mouse::handle(const mouse_release_event& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < mouse_btn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
