#include "dk/sys/events/KeyPressEvent.h"
#include "dk/sys/events/KeyReleaseEvent.h"
#include "dk/sys/EventManager.h"
#include "dk/sys/Keyboard.h"
#include "dk/Assert.h"
#include "dk/Core.h" // TODO: remove

#define KEYBOARD_ASCII(btn, l, h) \
	s_ASCII[(int)btn] = l; \
	s_ASCII[(int)btn + KeyboardBtnCount] = h;

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

/* static */ bool Keyboard::is_shift_pressed() noexcept
{
	return sys::Keyboard::state(sys::KeyboardBtn::LEFT_SHIFT)
		|| sys::Keyboard::state(sys::KeyboardBtn::RIGHT_SHIFT);
}

/* static */ char Keyboard::to_ASCII(KeyboardBtn btn) noexcept
{
	return s_ASCII[(int)btn + is_shift_pressed() * KeyboardBtnCount];
}

/* static */ char Keyboard::to_upper_ASCII(char c) noexcept
{
	if (c >= 'a' && c <= 'z')
		return c & ~(1 << 5);

	return c;
}

/* static */ Status Keyboard::create() noexcept
{
	KEYBOARD_ASCII(KeyboardBtn::TAB,   '\t', '\t');
	KEYBOARD_ASCII(KeyboardBtn::ENTER, '\n', '\n');
	KEYBOARD_ASCII(KeyboardBtn::SPACE, ' ',  ' ');

	KEYBOARD_ASCII(KeyboardBtn::MINUS, '-', '_');
	KEYBOARD_ASCII(KeyboardBtn::EQUAL, '=', '+');

	KEYBOARD_ASCII(KeyboardBtn::TILDE,         '`',  '~');
	KEYBOARD_ASCII(KeyboardBtn::LEFT_BRACKET,  '[',  '{');
	KEYBOARD_ASCII(KeyboardBtn::RIGHT_BRACKET, ']',  '}');
	KEYBOARD_ASCII(KeyboardBtn::BACKSLASH,     '\\', '|');
	KEYBOARD_ASCII(KeyboardBtn::SEMI_COLON,    ';',  ':');
	KEYBOARD_ASCII(KeyboardBtn::QUOTE,         '\'', '"');
	KEYBOARD_ASCII(KeyboardBtn::COMMA,         ',',  '<');
	KEYBOARD_ASCII(KeyboardBtn::PERIOD,        '.',  '>');
	KEYBOARD_ASCII(KeyboardBtn::SLASH,         '/',  '?');

	KEYBOARD_ASCII(KeyboardBtn::BTN_1, '1', '!');
	KEYBOARD_ASCII(KeyboardBtn::BTN_2, '2', '@');
	KEYBOARD_ASCII(KeyboardBtn::BTN_3, '3', '#');
	KEYBOARD_ASCII(KeyboardBtn::BTN_4, '4', '$');
	KEYBOARD_ASCII(KeyboardBtn::BTN_5, '5', '%');
	KEYBOARD_ASCII(KeyboardBtn::BTN_6, '6', '^');
	KEYBOARD_ASCII(KeyboardBtn::BTN_7, '7', '&');
	KEYBOARD_ASCII(KeyboardBtn::BTN_8, '8', '*');
	KEYBOARD_ASCII(KeyboardBtn::BTN_9, '9', '(');
	KEYBOARD_ASCII(KeyboardBtn::BTN_0, '0', ')');

	KEYBOARD_ASCII(KeyboardBtn::A, 'a', 'A');
	KEYBOARD_ASCII(KeyboardBtn::B, 'b', 'B');
	KEYBOARD_ASCII(KeyboardBtn::C, 'c', 'C');
	KEYBOARD_ASCII(KeyboardBtn::D, 'd', 'D');
	KEYBOARD_ASCII(KeyboardBtn::E, 'e', 'E');
	KEYBOARD_ASCII(KeyboardBtn::F, 'f', 'F');
	KEYBOARD_ASCII(KeyboardBtn::G, 'g', 'G');
	KEYBOARD_ASCII(KeyboardBtn::H, 'h', 'H');
	KEYBOARD_ASCII(KeyboardBtn::I, 'i', 'I');
	KEYBOARD_ASCII(KeyboardBtn::J, 'j', 'J');
	KEYBOARD_ASCII(KeyboardBtn::K, 'k', 'K');
	KEYBOARD_ASCII(KeyboardBtn::L, 'l', 'L');
	KEYBOARD_ASCII(KeyboardBtn::M, 'm', 'M');
	KEYBOARD_ASCII(KeyboardBtn::N, 'n', 'N');
	KEYBOARD_ASCII(KeyboardBtn::O, 'o', 'O');
	KEYBOARD_ASCII(KeyboardBtn::P, 'p', 'P');
	KEYBOARD_ASCII(KeyboardBtn::Q, 'q', 'Q');
	KEYBOARD_ASCII(KeyboardBtn::R, 'r', 'R');
	KEYBOARD_ASCII(KeyboardBtn::S, 's', 'S');
	KEYBOARD_ASCII(KeyboardBtn::T, 't', 'T');
	KEYBOARD_ASCII(KeyboardBtn::U, 'u', 'U');
	KEYBOARD_ASCII(KeyboardBtn::V, 'v', 'V');
	KEYBOARD_ASCII(KeyboardBtn::W, 'w', 'W');
	KEYBOARD_ASCII(KeyboardBtn::X, 'x', 'X');
	KEYBOARD_ASCII(KeyboardBtn::Y, 'y', 'Y');
	KEYBOARD_ASCII(KeyboardBtn::Z, 'z', 'Z');
	return Status::OK;
}

void Keyboard::handle(const KeyPressEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);

	s_state[(int)e.btn()] = true;
	if (e.btn() == KeyboardBtn::CAPS_LOCK)
		s_caps_lock_state = !s_caps_lock_state;

	// TODO: remove
	if (e.btn() == KeyboardBtn::Q && this->state(KeyboardBtn::LEFT_ALT))
		Core::get().stop();
}

void Keyboard::handle(const KeyReleaseEvent& e) noexcept /* override */
{
	DK_ASSERT(e.btn() < KeyboardBtn::ENUM_SIZE);
	s_state[(int)e.btn()] = false;
}

}
