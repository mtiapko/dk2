#ifndef __DK_SYS_KEY_RELEASE_EVENT_H__
#define __DK_SYS_KEY_RELEASE_EVENT_H__

#include "sys/Event.h"
#include "sys/Keyboard.h"

namespace dk::sys
{

class KeyReleaseEvent : public Event
{
private:
	KeyboardBtn m_btn;

public:
	KeyReleaseEvent(KeyboardBtn btn) noexcept : m_btn(btn) {}

	KeyboardBtn btn() const noexcept { return m_btn; }
};

}

#endif  //  !__DK_SYS_KEY_RELEASE_EVENT_H__
