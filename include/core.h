#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include <type_traits>
#include "graphic/render_system.h"

namespace dk
{

class core
{
private:
	static inline render_system s_active_render_sys;

public:
	static ret_code create() { return s_active_render_sys.create(); }

	static render_system* get_render_sys() { return &s_active_render_sys; }
};

}

#endif  //  !__DK_CORE_H__
