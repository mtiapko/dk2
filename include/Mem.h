#ifndef __DK_MEM_H__
#define __DK_MEM_H__

#include <stdlib.h> /* too prevent including of it after defines in this file */
#include "allocs/MemStd.h"

#define mem_alloc(size)        Mem::alloc(__FILE__, __func__, __LINE__, size)
#define mem_dealloc(ptr)       Mem::dealloc(__FILE__, __func__, __LINE__, ptr)
#define mem_realloc(ptr, size) Mem::realloc(__FILE__, __func__, __LINE__, ptr, size)

#define mem_create(T, ...) Mem::create<T>(__FILE__, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#define mem_destroy(ptr)   Mem::destroy(__FILE__, __func__, __LINE__, ptr)

namespace dk
{

using Mem = MemStd;

}

#endif  //  !__DK_MEM_H__
