#include <GL/glew.h>
#include "graphic/render_system.h"
#include "log.h"

namespace dk
{

bool render_system::s_is_init;

render_window* render_system::create_window()
{
	auto& render_window = m_windows.emplace_back();
	return &render_window;
}

ret_code render_system::init()
{
	if (!s_is_init) {
		auto err = glewInit();
		if (err != GLEW_NO_ERROR) {
			DK_LOG_ERROR("Failed to initialize GLEW: ", glewGetErrorString(err), ". Note: use 'glew-wayland' from aur");
			//return ret_code::ERORR;  //  TODO: user glew-wayland
		}

		s_is_init = true;
		DK_LOG_OK("GLEW ", glewGetString(GLEW_VERSION), " initialized");
	}

	return ret_code::OK;
}

ret_code render_system::create()
{
	return ret_code::OK;
}

}
