#ifndef __DK_OS_WINDOW_DATA_H__
#define __DK_OS_WINDOW_DATA_H__

#include "dk/containers/StringView.h"
#include "dk/containers/String.h"
#include "dk/Resource.h"

namespace dk::os
{

struct WindowData final : public Resource
{
	DK_RESOURCE_TYPE_INFO(WINDOW_DATA);

	// XXX: keep title less then 16 symbol (small string optimization)
	static constexpr StringView DEFAULT_TITLE = "Dvokutnik App";
	static constexpr uint16_t   CENTER_X = -1;
	static constexpr uint16_t   CENTER_Y = -1;

	String   title  = String(DEFAULT_TITLE);
	uint16_t x      = CENTER_X;
	uint16_t y      = CENTER_Y;
	uint16_t width  = 800;
	uint16_t height = 600;
	bool     v_sync = true;
};

}

#endif // !__DK_OS_WINDOW_DATA_H__
