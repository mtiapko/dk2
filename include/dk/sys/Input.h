#ifndef __DK_SYS_INPUT_H__
#define __DK_SYS_INPUT_H__

#include "dk/Status.h"

namespace dk::sys
{

class Input
{
public:
	static void update() noexcept;

	static Status create() noexcept;
};

}

#endif  //  !__DK_SYS_INPUT_H__
