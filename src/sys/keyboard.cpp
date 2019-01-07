#include "sys/events/key_press_event.h"
#include "sys/events/key_release_event.h"
#include "sys/event_manager.h"
#include "sys/keyboard.h"
#include "assert.h"

namespace dk::sys
{

/* static */ keyboard keyboard::s_this;

/* static */ bool keyboard::s_state[(int)keyboard_btn::ENUM_SIZE];

/* static */ void keyboard::record_input(bool val) noexcept
{
	if (val) {
		event_manager<key_press_event>::get().subscribe(&s_this);
		event_manager<key_release_event>::get().subscribe(&s_this);
	} else {
		//  TODO: remove
	}
}

void keyboard::handle(const key_press_event& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < keyboard_btn::ENUM_SIZE);
	s_state[(int)e.btn()] = true;
}

void keyboard::handle(const key_release_event& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < keyboard_btn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
