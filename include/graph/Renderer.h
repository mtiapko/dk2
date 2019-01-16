#ifndef __DK_GRAPH_RENDERER_H__
#define __DK_GRAPH_RENDERER_H__

#include "containers/Vector.h"
#include "graph/Window.h"

namespace dk::graph
{

class Renderer
{
private:
	static bool s_is_init;

	Vector<Window> m_windows;

public:
	Window* create_window() noexcept;

	Status create() noexcept;
};

}

#endif  //  !__DK_GRAPH_RENDERER_H__
