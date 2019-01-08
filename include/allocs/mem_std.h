#ifndef __DK_MEM_STD_H__
#define __DK_MEM_STD_H__

#include <utility>
#include "containers/string_view.h"

namespace dk
{

class mem_std
{
public:
	static void* alloc(string_view file, string_view func, size_t line, size_t size) noexcept;
	static void  dealloc(string_view file, string_view func, size_t line, void* ptr) noexcept;
	static void* realloc(string_view file, string_view func, size_t line, void* ptr, size_t new_size) noexcept;

	template<typename T, typename... Args>
	static T* create(string_view file, string_view func, size_t line, Args&&... args) noexcept
	{
		return new(alloc(file, func, line, sizeof(T))) T(std::forward<Args>(args)...);
	}

	template<typename T>
	static void destroy(string_view file, string_view func, size_t line, T* t) noexcept
	{
		if (t != nullptr) {
			t->~T();
			dealloc(file, func, line, t);
		}
	}
};

}

#endif  //  !__DK_MEM_STD_H__
