#ifndef __DK_SYS_MOUSE_H__
#define __DK_SYS_MOUSE_H__

#include "sys/EventListener.h"

namespace dk::sys
{

enum class MouseBtn
{
	UNKNOWN = 0,
	LEFT,
	MIDDLE,
	RIGHT,
	SCROLL_UP,
	SCROLL_DOWN,
	ENUM_SIZE
};

class Mouse : public
	EventListener<class MouseMoveEvent>,
	EventListener<class MousePressEvent>,
	EventListener<class MouseReleaseEvent>
{
private:
	static Mouse s_this;

	static bool s_state[(int)MouseBtn::ENUM_SIZE];
	static int  s_x;
	static int  s_y;
	static int  s_dx;
	static int  s_dy;

public:
	static void record_input(bool val) noexcept;

	static bool state(MouseBtn btn) noexcept { return s_state[(int)btn]; }
	static int x() noexcept { return s_x; }
	static int y() noexcept { return s_y; }
	static int dx() noexcept { return s_dx; }
	static int dy() noexcept { return s_dy; }

	static void set_dx(int dx) noexcept { s_dx = dx; }
	static void set_dy(int dy) noexcept { s_dy = dy; }

	void handle(const class MouseMoveEvent& e) noexcept override;
	void handle(const class MousePressEvent& e) noexcept override;
	void handle(const class MouseReleaseEvent& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
