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
	SCROLL_DOWN,
	SCROLL_UP,
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

public:
	static void record_input(bool val) noexcept;

	static bool state(MouseBtn btn) noexcept { return s_state[(int)btn]; }
	static int x() noexcept { return s_x; }
	static int y() noexcept { return s_y; }

	void handle(const class MouseMoveEvent& e) noexcept override;
	void handle(const class MousePressEvent& e) noexcept override;
	void handle(const class MouseReleaseEvent& e) noexcept override;
};

}

#endif  //  !__DK_SYS_KEYBOARD_H__
