#ifndef __DK_MEM_STD_H__
#define __DK_MEM_STD_H__

#include "containers/string_view.h"

namespace dk
{

class mem_std
{
public:
	static void* alloc(size_t size, string_view file, string_view func, size_t line) noexcept;
	static void  dealloc(void* ptr, string_view file, string_view func, size_t line) noexcept;
	static void* realloc(void* ptr, size_t new_size, string_view file, string_view func, size_t line) noexcept;
};

}

#endif  //  !__DK_MEM_STD_H__
