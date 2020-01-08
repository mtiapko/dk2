#ifndef __DK_GRAPH_RENDER_TARGET_H__
#define __DK_GRAPH_RENDER_TARGET_H__

namespace dk::graph
{

class RenderTarget
{
public:
	virtual void enable() noexcept = 0;
	virtual void disable() noexcept = 0;
};

}

#endif  //  !__DK_GRAPH_RENDER_TARGET_H__
