#ifndef __DK_GRAPH_RENDERER_MODULE_H__
#define __DK_GRAPH_RENDERER_MODULE_H__

namespace dk::graph
{

enum class RendererModuleID
{
	CUBE_MAP = 0
};

template<RendererModuleID ID>
class RendererModule
{
public:
	static RendererModuleID renderer_module_id() noexcept { return ID; }
};

}

#endif  //  !__DK_GRAPH_RENDERER_MODULE_H__
