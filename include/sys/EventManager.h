#ifndef __DK_SYS_EVENT_MANAGER_H__
#define __DK_SYS_EVENT_MANAGER_H__

#include "containers/Vector.h"
#include "sys/EventListener.h"

namespace dk::sys
{

template<typename EventT>
class EventManager
{
private:
	Vector<EventListener<EventT>*> m_listeners;

public:
	static EventManager& get() noexcept { static EventManager mgr; return mgr; }

	void subscribe(EventListener<EventT>* listener) noexcept
	{
		//  TODO: check is unique
		m_listeners.emplace_back(listener);
	}

	//  TODO: unsubscribe()

	template<typename... Args>
	void send(Args&&... args) const noexcept
	{
		EventT e(std::forward<Args>(args)...);
		for (auto& l: m_listeners)
			l->handle(e);
	}
};

}

#endif  //  !__DK_SYS_EVENT_MANAGER_H__
