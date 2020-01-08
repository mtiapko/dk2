#ifndef __DK_SYS_EVENT_LISTENER_H__
#define __DK_SYS_EVENT_LISTENER_H__

namespace dk::sys
{

template<typename EventT>
class EventListener
{
public:
	virtual void handle(const EventT&) noexcept {};
	virtual void handle() noexcept {};
};

}

#endif // !__DK_SYS_EVENT_LISTENER_H__
