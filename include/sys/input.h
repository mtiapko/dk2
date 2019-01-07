#ifndef __DK_SYS_INPUT_H__
#define __DK_SYS_INPUT_H__

#include "status.h"

namespace dk::sys
{

class input
{
public:
	static void update() noexcept;

	static status create() noexcept;
};

}

#endif  //  !__DK_SYS_INPUT_H__
