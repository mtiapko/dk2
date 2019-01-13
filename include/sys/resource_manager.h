#ifndef __DK_SYS_RESOURCE_MANAGER_H__
#define __DK_SYS_RESOURCE_MANAGER_H__

#include "sys/resource_loader.h"
#include "containers/hash_table.h"

namespace dk::sys
{

class resource_manager
{
private:
	static hash_table<string_view, resource_loader*> s_loaders;

public:
	template<typename T>
	static T* load(string_view file_path /* , resource_type type = T::type() */) noexcept
	{
		return static_cast<T*>(load(file_path, T::type()));
	}

	template<typename T>
	static status load(T& t, string_view file_path /* , resource_type type = T::type() */) noexcept
	{
		return load(static_cast<resource&>(t), file_path, T::type());
	}

	static resource* load(string_view file_path, resource_type type) noexcept;
	static status load(resource& res, string_view file_path, resource_type type) noexcept;

	static string_view mime(string_view file_path) noexcept;
	static resource_loader* loader(string_view mime) noexcept;

	static void add(resource_loader* loader, string_view mime) noexcept;
	static void remove(string_view mime) noexcept;
};

}

#endif  //  !__DK_SYS_RESOURCE_MANAGER_H__
