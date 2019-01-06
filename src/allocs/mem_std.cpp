#include <stdlib.h>
#include "allocs/mem_std.h"

namespace dk
{

/* static */ uint8_t* mem_std::alloc(size_t size, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for allocation
	(void)file;
	(void)func;
	(void)line;
	return (uint8_t*)malloc(size);
}

/* static */ void mem_std::dealloc(uint8_t* ptr, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for deallocation
	(void)file;
	(void)func;
	(void)line;
	return free(ptr);
}

/* static */ uint8_t* mem_std::realloc(uint8_t* ptr, size_t new_size, string_view file, string_view func, size_t line) noexcept
{
	//  TODO: write logging for reallocation
	(void)file;
	(void)func;
	(void)line;
	return (uint8_t*)::realloc(ptr, new_size);
}

}
