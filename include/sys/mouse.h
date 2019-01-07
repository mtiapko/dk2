#ifndef __DK_SYS_MOUSE_H__
#define __DK_SYS_MOUSE_H__

#include "sys/event_listener.h"

namespace dk::sys
{

enum class mouse_btn
{
	UNKNOWN = 0,
	LEFT,
	MIDDLE,
	RIGHT,
	SCROLL_DOWN,
	SCROLL_UP,
	ENUM_SIZE
};

class mouse : public
	event_listener<class mouse_move_event>,
	event_listener<class mouse_press_event>,
	event_listener<class mouse_release_event>
{
private:
	static mouse s_this;

	static bool s_state[(int)mouse_btn::ENUM_SIZE];
	static int  s_x;
	static int  s_y;

public:
	static void record_input(bool val) noexcept;

	static bool state(mouse_btn btn) noexcept { return s_state[(int)btn]; }
	static int x() noexcept { return s_x; }
	static int y() noexcept { return s_y; }

	void handle(const class mouse_move_event& e) noexcept override;
	void handle(const class mouse_press_event& e) noexcept override;
	void handle(const class mouse_release_event& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
