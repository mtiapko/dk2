#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include "sys/renderer.h"

namespace dk
{

class core
{
private:
	static sys::renderer s_active_renderer;

public:
	template<typename T> static T* active() noexcept;

	static status run() noexcept;

	static status create() noexcept;
};

}

#endif  //  !__DK_CORE_H__
