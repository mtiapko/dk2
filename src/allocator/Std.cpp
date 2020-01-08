#include <stdlib.h>
#include "dk/allocator/Std.h"

namespace dk::allocator
{

/* static */ void* Std::alloc(StringView file, StringView func, size_t line, size_t size) noexcept
{
	// TODO: write logging for allocation
	(void)file;
	(void)func;
	(void)line;
	return ::malloc(size);
}

/* static */ void Std::dealloc(StringView file, StringView func, size_t line, void* ptr) noexcept
{
	// TODO: write logging for deallocation
	(void)file;
	(void)func;
	(void)line;
	return ::free(ptr);
}

/* static */ void* Std::realloc(StringView file, StringView func, size_t line, void* ptr, size_t new_size) noexcept
{
	// TODO: write logging for reallocation
	(void)file;
	(void)func;
	(void)line;
	return ::realloc(ptr, new_size);
}

}
