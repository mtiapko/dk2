#ifndef __DK_GRAPH_WINDOW_DATA_H__
#define __DK_GRAPH_WINDOW_DATA_H__

#include "dk/containers/StringView.h"
#include "dk/containers/String.h"

namespace dk::graph
{

struct WindowData // TODO: inherit from ResourceData<>?
{
	// XXX: keep title less then 16 symbol (small string optimization)
	static constexpr StringView DEFAULT_TITLE = "Dvokutnik App";
	static constexpr uint16_t   CENTER_X = -1;
	static constexpr uint16_t   CENTER_Y = -1;

	String   title  = String(DEFAULT_TITLE);
	uint16_t x      = CENTER_X;
	uint16_t y      = CENTER_Y;
	uint16_t width  = 1920;
	uint16_t height = 1080;
	bool     v_sync = true;
};

}

#endif // !__DK_GRAPH_WINDOW_DATA_H__
