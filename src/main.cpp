#include "log.h"
#include "sys/core.h"

using namespace dk;
using namespace dk::sys;

int main()
{
	if (auto res = core::create(); !res)
		return res;

	if (auto res = core::run(); !res)
		return res;

	return 0;
}
