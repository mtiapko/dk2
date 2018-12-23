#ifndef __DK_SYS_CORE_H__
#define __DK_SYS_CORE_H__

#include "sys/renderer.h"

namespace dk::sys
{

class core
{
private:
	static renderer s_active_renderer;

public:
	template<typename T> static T* active() noexcept;

	static status run() noexcept;

	static status create() noexcept;
};

}

#endif  //  !__DK_SYS_CORE_H__
