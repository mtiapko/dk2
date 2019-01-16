#include "sys/events/KeyPressEvent.h"
#include "sys/events/KeyReleaseEvent.h"
#include "sys/EventManager.h"
#include "sys/Keyboard.h"
#include "Assert.h"

namespace dk::sys
{

/* static */ Keyboard Keyboard::s_this;

/* static */ bool Keyboard::s_state[(int)KeyboardBtn::ENUM_SIZE];

/* static */ void Keyboard::record_input(bool val) noexcept
{
	if (val) {
		EventManager<KeyPressEvent>::get().subscribe(&s_this);
		EventManager<KeyReleaseEvent>::get().subscribe(&s_this);
	} else {
		//  TODO: remove
	}
}

void Keyboard::handle(const KeyPressEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = true;
}

void Keyboard::handle(const KeyReleaseEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
