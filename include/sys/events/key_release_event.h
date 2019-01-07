#ifndef __DK_SYS_KEY_RELEASE_EVENT_H__
#define __DK_SYS_KEY_RELEASE_EVENT_H__

#include "sys/event.h"
#include "sys/keyboard.h"

namespace dk::sys
{

class key_release_event : public event
{
private:
	keyboard_btn m_btn;

public:
	key_release_event(keyboard_btn btn) noexcept : m_btn(btn) {}

	keyboard_btn btn() const noexcept { return m_btn; }
};

}

#endif  //  !__DK_SYS_KEY_RELEASE_EVENT_H__
