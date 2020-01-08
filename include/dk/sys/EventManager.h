#ifndef __DK_SYS_EVENT_MANAGER_H__
#define __DK_SYS_EVENT_MANAGER_H__

#include "dk/containers/Vector.h"
#include "dk/util/TypeInfo.h"
#include "dk/sys/EventListener.h"

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
		//  TODO: check if unique
		//  TODO: check if right method overloaded
		m_listeners.emplace_back(listener);
	}

	//  TODO: unsubscribe()

	template<typename... Args>
	void send(Args&&... args) const noexcept
	{
		if constexpr (util::TypeInfo::is_empty_object_v<EventT>) {
			for (auto& l: m_listeners)
				l->handle();
		} else {
			EventT e(std::forward<Args>(args)...);
			for (auto& l: m_listeners)
				l->handle(e);
		}
	}
};

}

#endif // !__DK_SYS_EVENT_MANAGER_H__
