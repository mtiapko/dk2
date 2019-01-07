#include <GL/glew.h>
#include "graph/renderer.h"
#include "log.h"

namespace dk::graph
{

/* static */ bool renderer::s_is_init = false;

window* renderer::create_window() noexcept
{
	auto& wnd = m_windows.emplace_back();
	return &wnd;
}

status renderer::create() noexcept
{
	if (!s_is_init) {
		auto ret = glewInit();
		if (ret != GLEW_NO_ERROR) {
			DK_LOG_ERROR("Failed to initialize GLEW: ", glewGetString(ret), ". Note: use 'glew-wayland' from AUR");
			//  return status::ERROR;  TODO: use glew-wayland
		}

		s_is_init = true;
		DK_LOG_OK("GLEW ", glewGetString(GLEW_VERSION), " initalized");
	}

	DK_LOG_OK("Graphic renderer created");
	return status::OK;
}

}
