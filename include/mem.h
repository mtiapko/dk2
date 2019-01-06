#ifndef __DK_MEM_H__
#define __DK_MEM_H__

#include "allocs/mem_std.h"

#define alloc(size)        alloc(size, __FILE__, __func__, __LINE__)
#define dealloc(ptr)       dealloc(ptr, __FILE__, __func__, __LINE__)
#define realloc(ptr, size) realloc(ptr, size, __FILE__, __func__, __LINE__)

namespace dk
{

using mem = mem_std;

}

#endif  //  !__DK_MEM_H__
