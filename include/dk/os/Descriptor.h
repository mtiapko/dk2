#ifndef __DK_OS_DESCRIPTOR_H__
#define __DK_OS_DESCRIPTOR_H__

// TODO: #ifdef
#include <X11/Xlib.h>
#undef Status /* XXX: Xlib... */

#include "dk/Status.h"

namespace dk::os
{

class Descriptor
{
private:
	// TODO: #ifdef
	static inline Display* s_display = nullptr;

public:
	static Display* get() noexcept { return s_display; }

	static Status create() noexcept;
};

}

#endif // !__DK_OS_DESCRIPTOR_H__
