#ifndef __DK_EVENT_SYSTEM_H__
#define __DK_EVENT_SYSTEM_H__

#include "event_listener.h"
#include "containers/vector.h"

namespace dk
{

template<typename EventType>
class event_system
{
private:
	//static_assert(std::is_base_of_v<event, EventType>, "Maybe event would have some fields in the future");

	vector<event_listener<EventType>*> m_listeners;

public:
	static event_system& get() { static event_system sys; return sys; }

	template<typename... Args> void send(Args&&... args)
	{
		EventType e(std::forward<Args>(args)...);
		for (auto& l: m_listeners)
			l->handle(e);
	}

	void subscribe(event_listener<EventType>* listener)
	{
		m_listeners.emplace_back(listener);
	}
};

template<typename... EventTypes>
class event_system<event_category<EventTypes...>>
{
private:
	//  TODO: another send for event_category???
	//static_assert(std::is_base_of_v<event, EventType>, "Maybe event would have some fields in the future");

public:
	static void subscribe(event_listener<event_category<EventTypes...>>* listener)
	{
		(event_system<EventTypes>::get().subscribe(listener), ...);
	}
};

}

#endif  //  !__DK_EVENT_SYSTEM_H__
