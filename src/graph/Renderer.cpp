#include <GL/glew.h>
#include "graph/GUI.h"
#include "graph/CubeMap.h"
#include "graph/Renderer.h"
#include "Log.h"

namespace dk::graph
{

/* static */ bool Renderer::s_is_init = false;

Status Renderer::init_module(RendererModuleID module_id) noexcept
{
	switch (module_id) {
		case RendererModuleID::CUBE_MAP: return CubeMap::init();
		default:
			DK_LOG_ERROR("Renderer does not support module with ID #", (int)module_id);
			return Status::ERROR;
	}
}

Window* Renderer::create_window() noexcept
{
	auto& wnd = m_windows.emplace_back();
	return &wnd;
}

Status Renderer::create() noexcept
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
	if (auto ret = GUI::create(); !ret)
		return ret;

	return Status::OK;
}

}
