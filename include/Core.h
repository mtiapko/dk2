#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include "Application.h"
#include "graph/Renderer.h"

namespace dk
{

class Core
{
private:
	static bool            s_running;
	static graph::Renderer s_active_renderer;

public:
	template<typename T> static T* active() noexcept;

	static Status run(Application* app) noexcept;
	static void stop() noexcept;

	//  TODO: enum create all, only audio, only net, ... (multi using overloaded AND '&&')
	static Status create() noexcept;
	static void destroy() noexcept;
};

}

#endif  //  !__DK_CORE_H__
