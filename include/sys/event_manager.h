#ifndef __DK_SYS_EVENT_MANAGER_H__
#define __DK_SYS_EVENT_MANAGER_H__

//#include <utility>
#include "containers/vector.h"
#include "sys/event_listener.h"

namespace dk::sys
{

template<typename EventT>
class event_manager
{
private:
	vector<event_listener<EventT>*> m_listeners;

public:
	static event_manager& get() noexcept { static event_manager mgr; return mgr; }

	void subscribe(event_listener<EventT>* listener) noexcept
	{
		//  TODO: check is unique
		m_listeners.emplace_back(listener);
	}

	//  TODO: unsubscribe()

	template<typename... Args>
	void send(Args&&... args) const noexcept
	{
		//EventT e(std::forward<Args>(args)...);
		EventT e(args...);
		for (auto& l: m_listeners)
			l->handle(e);
	}
};

}

#endif  //  !__DK_SYS_EVENT_MANAGER_H__
