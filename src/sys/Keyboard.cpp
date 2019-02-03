#include "sys/events/KeyPressEvent.h"
#include "sys/events/KeyReleaseEvent.h"
#include "sys/EventManager.h"
#include "sys/Keyboard.h"
#include "Assert.h"

namespace dk::sys
{

/* static */ Keyboard Keyboard::s_this;
/* static */ char     Keyboard::s_ASCII[];
/* static */ bool     Keyboard::s_caps_lock_state;

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

/* static */ bool Keyboard::is_printable(KeyboardBtn btn) noexcept
{
	return s_ASCII[(int)btn];
}

/* static */ char Keyboard::to_ASCII(KeyboardBtn btn) noexcept
{
	return s_ASCII[(int)btn];
}

/* static */ char Keyboard::to_upper_ASCII(char c) noexcept
{
	if (c >= 'a' && c <= 'z')
		return c & ~(1 << 5);

	return c;
}

/* static */ Status Keyboard::create() noexcept
{
	s_ASCII[(int)KeyboardBtn::TAB]   = '\t';
	s_ASCII[(int)KeyboardBtn::ENTER] = '\n';
	s_ASCII[(int)KeyboardBtn::SPACE] = ' ';

	s_ASCII[(int)KeyboardBtn::BTN_1] = '1';
	s_ASCII[(int)KeyboardBtn::BTN_2] = '2';
	s_ASCII[(int)KeyboardBtn::BTN_3] = '3';
	s_ASCII[(int)KeyboardBtn::BTN_4] = '4';
	s_ASCII[(int)KeyboardBtn::BTN_5] = '5';
	s_ASCII[(int)KeyboardBtn::BTN_6] = '6';
	s_ASCII[(int)KeyboardBtn::BTN_7] = '7';
	s_ASCII[(int)KeyboardBtn::BTN_8] = '8';
	s_ASCII[(int)KeyboardBtn::BTN_9] = '9';
	s_ASCII[(int)KeyboardBtn::BTN_0] = '0';

	s_ASCII[(int)KeyboardBtn::A] = 'a';
	s_ASCII[(int)KeyboardBtn::B] = 'b';
	s_ASCII[(int)KeyboardBtn::C] = 'c';
	s_ASCII[(int)KeyboardBtn::D] = 'd';
	s_ASCII[(int)KeyboardBtn::E] = 'e';
	s_ASCII[(int)KeyboardBtn::F] = 'f';
	s_ASCII[(int)KeyboardBtn::G] = 'g';
	s_ASCII[(int)KeyboardBtn::H] = 'h';
	s_ASCII[(int)KeyboardBtn::I] = 'i';
	s_ASCII[(int)KeyboardBtn::J] = 'j';
	s_ASCII[(int)KeyboardBtn::K] = 'k';
	s_ASCII[(int)KeyboardBtn::L] = 'l';
	s_ASCII[(int)KeyboardBtn::M] = 'm';
	s_ASCII[(int)KeyboardBtn::N] = 'n';
	s_ASCII[(int)KeyboardBtn::O] = 'o';
	s_ASCII[(int)KeyboardBtn::P] = 'p';
	s_ASCII[(int)KeyboardBtn::Q] = 'q';
	s_ASCII[(int)KeyboardBtn::R] = 'r';
	s_ASCII[(int)KeyboardBtn::S] = 's';
	s_ASCII[(int)KeyboardBtn::T] = 't';
	s_ASCII[(int)KeyboardBtn::U] = 'u';
	s_ASCII[(int)KeyboardBtn::V] = 'v';
	s_ASCII[(int)KeyboardBtn::W] = 'w';
	s_ASCII[(int)KeyboardBtn::X] = 'x';
	s_ASCII[(int)KeyboardBtn::Y] = 'y';
	s_ASCII[(int)KeyboardBtn::Z] = 'z';
	return Status::OK;
}

void Keyboard::handle(const KeyPressEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);

	s_state[(int)e.btn()] = true;
	if (e.btn() == KeyboardBtn::CAPS_LOCK)
		s_caps_lock_state = !s_caps_lock_state;
}

void Keyboard::handle(const KeyReleaseEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
