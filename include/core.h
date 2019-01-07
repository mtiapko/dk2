#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include "application.h"
#include "graph/renderer.h"

namespace dk
{

class core
{
private:
	static graph::renderer s_active_renderer;

public:
	template<typename T> static T* active() noexcept;

	static status run(application* app) noexcept;

	static status create() noexcept;
};

}

#endif  //  !__DK_CORE_H__
