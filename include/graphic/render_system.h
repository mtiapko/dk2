#ifndef __DK_RENDER_SYSTEM_H__
#define __DK_RENDER_SYSTEM_H__

#include "graphic/shader_program.h"
#include "graphic/render_window.h"
#include "containers/vector.h"

namespace dk
{

class render_system
{
private:
	static bool s_is_init;

	vector<render_window> m_windows;
	vector<shader> m_sahders;

public:
	render_window* create_window();

	bool is_init() const { return s_is_init; }

	status init();
	status create();
};

}

#endif  //  !__DK_RENDER_SYSTEM_H__
