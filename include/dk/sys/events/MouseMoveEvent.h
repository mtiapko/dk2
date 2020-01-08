#ifndef __DK_SYS_MOUSE_MOVE_EVENT_H__
#define __DK_SYS_MOUSE_MOVE_EVENT_H__

#include "dk/sys/Event.h"

namespace dk::sys
{

class MouseMoveEvent : public Event
{
private:
	int m_x;
	int m_y;

public:
	MouseMoveEvent(int x, int y) noexcept : m_x(x), m_y(y) {}

	int x() const noexcept { return m_x; }
	int y() const noexcept { return m_y; }
};

}

#endif // !__DK_SYS_MOUSE_MOVE_EVENT_H__
