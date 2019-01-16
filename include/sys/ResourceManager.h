#ifndef __DK_SYS_RESOURCE_MANAGER_H__
#define __DK_SYS_RESOURCE_MANAGER_H__

#include "sys/ResourceLoader.h"
#include "containers/HashTable.h"

namespace dk::sys
{

class ResourceManager
{
private:
	static HashTable<StringView, ResourceLoader*> s_loaders;

public:
	template<typename T>
	static T* load(StringView file_path /* , ResourceType type = T::type() */) noexcept
	{
		return static_cast<T*>(load(file_path, T::type()));
	}

	template<typename T>
	static Status load(T& t, StringView file_path /* , ResourceType type = T::type() */) noexcept
	{
		return load(static_cast<Resource&>(t), file_path, T::type());
	}

	static Resource* load(StringView file_path, ResourceType type) noexcept;
	static Status load(Resource& res, StringView file_path, ResourceType type) noexcept;

	static StringView mime(StringView file_path) noexcept;
	static ResourceLoader* loader(StringView mime) noexcept;

	static void add(ResourceLoader* loader, StringView mime) noexcept;
	static void remove(StringView mime) noexcept;
};

}

#endif  //  !__DK_SYS_RESOURCE_MANAGER_H__
