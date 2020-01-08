#ifndef __DK_SYS_MOUSE_RELEASE_EVENT_H__
#define __DK_SYS_MOUSE_RELEASE_EVENT_H__

#include "dk/sys/Event.h"
#include "dk/sys/Mouse.h"

namespace dk::sys
{

class MouseReleaseEvent : public Event
{
private:
	MouseBtn m_btn;

public:
	MouseReleaseEvent(MouseBtn btn) noexcept : m_btn(btn) {}

	MouseBtn btn() const noexcept { return m_btn; }
};

}

#endif // !__DK_SYS_MOUSE_RELEASE_EVENT_H__
