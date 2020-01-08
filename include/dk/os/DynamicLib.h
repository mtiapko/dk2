#ifndef __DK_OS_DYNAMIC_LIB_H__
#define __DK_OS_DYNAMIC_LIB_H__

// TODO: #ifdef DK_PLATFORM_GNU_LINUX...
#include <dlfcn.h>

#include "dk/containers/UniquePtr.h"
#include "dk/containers/StringView.h"
#include "dk/containers/String.h"
#include "dk/Status.h"

namespace dk::os
{

class DynamicLib
{
private:
	String m_path;
	UniquePtr<void, int (*)(void*)>  m_lib { nullptr, dlclose };
	// TODO: remove 'noexcept' from decltype(dlclose)* and use it

	void* load_func_impl(const String& name) const noexcept;

public:
	StringView path() const noexcept { return m_path; }

	template<typename FuncT = void>
	FuncT* load_func(const String& name) const noexcept
	{
		return (FuncT*)load_func_impl(name);
	}

	Status load(StringView path) noexcept;
};

}

#endif // !__DK_OS_DYNAMIC_LIB_H__
