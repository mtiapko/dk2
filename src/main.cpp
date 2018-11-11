#include "log.h"
#include "core.h"

int main()
{
	DK_LOG("Hello!");
	DK_LOG_WARNING("Hello!");
	DK_LOG_ERROR("Hello!");

	dk::render_system render_sys;
	if (render_sys.create() != dk::ret_code::OK)
		return -1;

	return 0;
}
