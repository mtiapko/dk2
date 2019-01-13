#ifndef __DK_SYS_KEYBOARD_H__
#define __DK_SYS_KEYBOARD_H__

#include "sys/event_listener.h"

namespace dk::sys
{

enum class keyboard_btn
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

class keyboard : public
	event_listener<class key_press_event>,
	event_listener<class key_release_event>
{
private:
	static keyboard s_this;

	static bool s_state[(int)keyboard_btn::ENUM_SIZE];

public:
	static void record_input(bool val) noexcept;

	static bool state(keyboard_btn btn) noexcept { return s_state[(int)btn]; }

	void handle(const class key_press_event& e) noexcept override;
	void handle(const class key_release_event& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
