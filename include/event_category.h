#ifndef __DK_EVENT_CATEGORY_H__
#define __DK_EVENT_CATEGORY_H__

#include <type_traits>
#include "event.h"

namespace dk
{

template<typename... EventTypes>
class event_category
{
private:
	//static_assert((std::is_base_of_v<event, EventTypes> && ...), "Maybe event would have some fields in the future");
};

}

#endif  //  !__DK_EVENT_CATEGORY_H__
