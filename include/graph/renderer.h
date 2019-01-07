#ifndef __DK_GRAPH_RENDERER_H__
#define __DK_GRAPH_RENDERER_H__

#include "containers/vector.h"
#include "graph/window.h"

namespace dk::graph
{

class renderer
{
private:
	static bool s_is_init;

	vector<window> m_windows;

public:
	window* create_window() noexcept;

	status create() noexcept;
};

}

#endif  //  !__DK_GRAPH_RENDERER_H__
