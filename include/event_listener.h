#ifndef __DK_EVENT_LISTENER_H__
#define __DK_EVENT_LISTENER_H__

#include <type_traits>
#include "event_category.h"

namespace dk
{

template<typename EventType>
class event_listener
{
private:
	//static_assert(std::is_base_of_v<event, EventType>, "Maybe event would have some fields in the future");

public:
	virtual void handle(const EventType& e) = 0;
	void handle() { this->handle({}); }
};

template<typename... EventTypes>
class event_listener<event_category<EventTypes...>> : public event_listener<EventTypes>... {};

}

#endif  //  !__DK_EVENT_LISTENER_H__
