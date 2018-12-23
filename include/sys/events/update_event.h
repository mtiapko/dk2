#ifndef __DK_SYS_EVENTS_UPDATE_EVENT_H__
#define __DK_SYS_EVENTS_UPDATE_EVENT_H__

#include "sys/event.h"

namespace dk::sys
{

class update_event : public event
{
private:
	float m_dt;

public:
	update_event(float dt) noexcept : m_dt(dt) {}

	float dt() const noexcept { return m_dt; }
};

}

#endif  //  !__DK_SYS_EVENTS_UPDATE_EVENT_H__
