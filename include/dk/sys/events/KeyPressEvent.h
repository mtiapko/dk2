#ifndef __DK_SYS_KEY_PRESS_EVENT_H__
#define __DK_SYS_KEY_PRESS_EVENT_H__

#include "dk/sys/Event.h"
#include "dk/sys/Keyboard.h"

namespace dk::sys
{

class KeyPressEvent : public Event
{
private:
	KeyboardBtn m_btn;

public:
	KeyPressEvent(KeyboardBtn btn) noexcept : m_btn(btn) {}

	KeyboardBtn btn() const noexcept { return m_btn; }
};

}

#endif // !__DK_SYS_KEY_PRESS_EVENT_H__
