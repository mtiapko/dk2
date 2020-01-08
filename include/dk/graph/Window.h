#ifndef __DK_GRAPH_WINDOW_H__
#define __DK_GRAPH_WINDOW_H__

#include "dk/graph/RenderTarget.h"
#include "dk/graph/WindowData.h"
#include "dk/Resource.h"
#include "dk/Status.h"

namespace dk::graph
{

class Window : public Resource, public RenderTarget
{
public:
	DK_RESOURCE_TYPE_INFO(WINDOW);

	virtual void render() noexcept = 0;

	virtual Status create(const WindowData& data = {}) noexcept = 0;
};

}

#endif // !__DK_GRAPH_WINDOW_H__
