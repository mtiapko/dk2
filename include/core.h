#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include <type_traits>
#include "status.h"

namespace dk
{

class core
{
private:
	static bool                s_running;
	static class render_system s_active_render_sys;
	static class application*  s_app;

public:
	static status run();
	static status create(class application* app);

	static class render_system* get_render_sys() { return &s_active_render_sys; }
};

}

#endif  //  !__DK_CORE_H__
