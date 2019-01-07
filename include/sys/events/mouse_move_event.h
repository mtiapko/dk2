#ifndef __DK_SYS_MOUSE_MOVE_EVENT_H__
#define __DK_SYS_MOUSE_MOVE_EVENT_H__

#include "sys/event.h"

namespace dk::sys
{

class mouse_move_event : public event
{
private:
	int m_x;
	int m_y;

public:
	mouse_move_event(int x, int y) noexcept : m_x(x), m_y(y) {}

	int x() const noexcept { return m_x; }
	int y() const noexcept { return m_y; }
};

}

#endif  //  !__DK_SYS_MOUSE_MOVE_EVENT_H__
