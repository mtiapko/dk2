#ifndef __DK_MEM_H__
#define __DK_MEM_H__

#include <stdlib.h> /* too prevent including of it after defines in this file */
#include "allocs/mem_std.h"

#define mem_alloc(size)        mem::alloc(__FILE__, __func__, __LINE__, size)
#define mem_dealloc(ptr)       mem::dealloc(__FILE__, __func__, __LINE__, ptr)
#define mem_realloc(ptr, size) mem::realloc(__FILE__, __func__, __LINE__, ptr, size)

#define mem_create(T, ...) mem::create<T>(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define mem_destroy(ptr)   mem::destroy(__FILE__, __func__, __LINE__, ptr)

namespace dk
{

using mem = mem_std;

}

#endif  //  !__DK_MEM_H__
