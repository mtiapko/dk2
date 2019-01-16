#include <stdlib.h>
#include "allocs/MemStd.h"

inline void* operator new(size_t size, dk::StringView file, dk::StringView func, size_t line)
{
	return dk::MemStd::alloc(file, func, line, size);
}

namespace dk
{

/* static */ void* MemStd::alloc(StringView file, StringView func, size_t line, size_t size) noexcept
{
	//  TODO: write logging for allocation
	(void)file;
	(void)func;
	(void)line;
	return malloc(size);
}

/* static */ void MemStd::dealloc(StringView file, StringView func, size_t line, void* ptr) noexcept
{
	//  TODO: write logging for deallocation
	(void)file;
	(void)func;
	(void)line;
	return free(ptr);
}

/* static */ void* MemStd::realloc(StringView file, StringView func, size_t line, void* ptr, size_t new_size) noexcept
{
	//  TODO: write logging for reallocation
	(void)file;
	(void)func;
	(void)line;
	return ::realloc(ptr, new_size);
}

}
