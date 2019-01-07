#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include "application.h"
#include "graph/renderer.h"

namespace dk
{

class core
{
private:
	static bool            s_running;
	static graph::renderer s_active_renderer;

public:
	template<typename T> static T* active() noexcept;

	static status run(application* app) noexcept;
	static void stop() noexcept;

	//  TODO: enum create all, only audio, only net, ... (multi using overloaded AND '&&')
	static status create() noexcept;
	static void destroy() noexcept;
};

}

#endif  //  !__DK_CORE_H__
