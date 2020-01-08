#ifndef __DK_MEM_H__
#define __DK_MEM_H__

#include "dk/allocator/Std.h"

#define dk_mem_alloc(size)        Allocator::alloc(__FILE__, __func__, __LINE__, size)
#define dk_mem_dealloc(ptr)       Allocator::dealloc(__FILE__, __func__, __LINE__, ptr)
#define dk_mem_realloc(ptr, size) Allocator::realloc(__FILE__, __func__, __LINE__, ptr, size)

#define dk_mem_new(T, ...) Allocator::create<T>(__FILE__, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#define dk_mem_delete(ptr) Allocator::destroy(__FILE__, __func__, __LINE__, ptr)

namespace dk
{

using Allocator = allocator::Std;

}

inline void* operator new(size_t size, dk::StringView file, dk::StringView func, size_t line) noexcept
{
	return dk::Allocator::alloc(file, func, line, size);
}

#endif // !__DK_MEM_H__
