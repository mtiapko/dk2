#ifndef __DK_GRAPH_RENDERER_H__
#define __DK_GRAPH_RENDERER_H__

#include "graph/Window.h"
#include "graph/RendererModule.h"
#include "containers/Vector.h"

namespace dk::graph
{

class Renderer
{
private:
	static bool s_is_init;

	Vector<Window> m_windows;

public:
	template<typename ModuleT>
	Status init_module() noexcept { return this->init_module(ModuleT::renderer_module_id()); }  //  TODO: not virtual (when plugin)
	Status init_module(RendererModuleID module_id) noexcept;

	Window* create_window() noexcept;

	Status create() noexcept;
};

}

#endif  //  !__DK_GRAPH_RENDERER_H__
