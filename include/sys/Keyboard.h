#ifndef __DK_SYS_KEYBOARD_H__
#define __DK_SYS_KEYBOARD_H__

#include "Status.h"
#include "sys/EventListener.h"

namespace dk::sys
{

enum class KeyboardBtn
{
	UNKNOWN = 0,
	ESCAPE,
	TAB,
	SPACE,
	BACK_SPACE,
	ENTER,
	DELETE,
	CAPS_LOCK,
	PAGE_UP,
	PAGE_DOWN,
	UP_ARROW,
	DOWN_ARROW,
	LEFT_ARROW,
	RIGHT_ARROW,

	LEFT_SHIFT,
	RIGHT_SHIFT,
	LEFT_CTRL,
	RIGHT_CTRL,
	LEFT_ALT,
	RIGHT_ALT,

	/* num row */   BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8, BTN_9, BTN_0,

	/* top row    */ Q, W, E, R, T, Y, U, I, O, P,
	/* middle row */  A, S, D, F, G, H, J, K, L,
	/* bottom row */   Z, X, C, V, B, N, M,

	ENUM_SIZE
};

class Keyboard : public
	EventListener<class KeyPressEvent>,
	EventListener<class KeyReleaseEvent>
{
private:
	static Keyboard s_this;

	static char s_ASCII[(int)KeyboardBtn::ENUM_SIZE];
	static bool s_state[(int)KeyboardBtn::ENUM_SIZE];
	static bool s_caps_lock_state;

public:
	static void record_input(bool val) noexcept;

	static bool is_printable(KeyboardBtn btn) noexcept;
	static char to_ASCII(KeyboardBtn btn) noexcept;
	static char to_upper_ASCII(char c) noexcept;

	static bool state(KeyboardBtn btn) noexcept { return s_state[(int)btn]; }
	static bool caps_lock_state() noexcept { return s_caps_lock_state; }

	static Status create() noexcept;

	void handle(const class KeyPressEvent& e) noexcept override;
	void handle(const class KeyReleaseEvent& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
