#include <stdlib.h>
#include "allocs/mem_std.h"

inline void* operator new(size_t size, dk::string_view file, dk::string_view func, size_t line)
{
	return dk::mem_std::alloc(file, func, line, size);
}

namespace dk
{

/* static */ void* mem_std::alloc(string_view file, string_view func, size_t line, size_t size) noexcept
{
	//  TODO: write logging for allocation
	(void)file;
	(void)func;
	(void)line;
	return malloc(size);
}

/* static */ void mem_std::dealloc(string_view file, string_view func, size_t line, void* ptr) noexcept
{
	//  TODO: write logging for deallocation
	(void)file;
	(void)func;
	(void)line;
	return free(ptr);
}

/* static */ void* mem_std::realloc(string_view file, string_view func, size_t line, void* ptr, size_t new_size) noexcept
{
	//  TODO: write logging for reallocation
	(void)file;
	(void)func;
	(void)line;
	return ::realloc(ptr, new_size);
}

}
