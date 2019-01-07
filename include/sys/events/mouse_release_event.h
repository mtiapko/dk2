#ifndef __DK_SYS_MOUSE_RELEASE_EVENT_H__
#define __DK_SYS_MOUSE_RELEASE_EVENT_H__

#include "sys/event.h"
#include "sys/mouse.h"

namespace dk::sys
{

class mouse_release_event : public event
{
private:
	mouse_btn m_btn;

public:
	mouse_release_event(mouse_btn btn) noexcept : m_btn(btn) {}

	mouse_btn btn() const noexcept { return m_btn; }
};

}

#endif  //  !__DK_SYS_MOUSE_RELEASE_EVENT_H__