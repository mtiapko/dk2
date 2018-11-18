#include "log.h"
#include "core.h"

int main()
{
	dk::render_system render_sys;
	if (render_sys.create() != dk::ret_code::OK)
		return -1;

	return 0;
}
