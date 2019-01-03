#ifndef __DK_SYS_RENDERER_H__
#define __DK_SYS_RENDERER_H__

#include "containers/vector.h"
#include "sys/renderer_window.h"

namespace dk::sys
{

class renderer
{
private:
	static bool s_is_init;

	vector<renderer_window> m_windows;

public:
	renderer_window* create_window() noexcept;

	status create() noexcept;
};

}

#endif  //  !__DK_SYS_RENDERER_H__
