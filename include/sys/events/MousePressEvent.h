#ifndef __DK_SYS_MOUSE_PRESS_EVENT_H__
#define __DK_SYS_MOUSE_PRESS_EVENT_H__

#include "sys/Event.h"
#include "sys/Mouse.h"

namespace dk::sys
{

class MousePressEvent : public Event
{
private:
	MouseBtn m_btn;

public:
	MousePressEvent(MouseBtn btn) noexcept : m_btn(btn) {}

	MouseBtn btn() const noexcept { return m_btn; }
};

}

#endif  //  !__DK_SYS_MOUSE_PRESS_EVENT_H__
