#include <stdlib.h>
#include "allocs/mem_std.h"

namespace dk
{

/* static */ void* mem_std::alloc(size_t size, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for allocation
	(void)file;
	(void)func;
	(void)line;
	return malloc(size);
}

/* static */ void mem_std::dealloc(void* ptr, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for deallocation
	(void)file;
	(void)func;
	(void)line;
	return free(ptr);
}

/* static */ void* mem_std::realloc(void* ptr, size_t new_size, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for reallocation
	(void)file;
	(void)func;
	(void)line;
	return ::realloc(ptr, new_size);
}

}
