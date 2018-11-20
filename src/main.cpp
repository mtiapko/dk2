#include "log.h"
#include "core.h"
#include "graphic/render_window.h"

int main()
{
	if (dk::core::create() != dk::ret_code::OK)
		return -1;

	dk::render_window wnd;
	if (wnd.create() != dk::ret_code::OK)
		return -1;

	std::cin.get();
	return 0;
}
