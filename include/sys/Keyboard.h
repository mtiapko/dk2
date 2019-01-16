#ifndef __DK_SYS_KEYBOARD_H__
#define __DK_SYS_KEYBOARD_H__

#include "sys/EventListener.h"

namespace dk::sys
{

enum class KeyboardBtn
{
	UNKNOWN = 0,
	ESCAPE,
	TAB,
	SPACE,
	ENTER,
	DELETE,
	UP_ARROW,
	DOWN_ARROW,
	LEFT_ARROW,
	RIGHT_ARROW,

	L_SHIFT,
	R_SHIFT,
	L_CTRL,
	R_CTRL,
	L_ALT,
	R_ALT,

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

	static bool s_state[(int)KeyboardBtn::ENUM_SIZE];

public:
	static void record_input(bool val) noexcept;

	static bool state(KeyboardBtn btn) noexcept { return s_state[(int)btn]; }

	void handle(const class KeyPressEvent& e) noexcept override;
	void handle(const class KeyReleaseEvent& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
