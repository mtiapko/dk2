#ifndef __DK_RESOURCE_MANAGER_H__
#define __DK_RESOURCE_MANAGER_H__

#include "sys/ResourceLoader.h"
#include "containers/HashTable.h"

namespace dk
{

class ResourceManager
{
private:
	static HashTable<StringView, sys::ResourceLoader*> s_loaders;

public:
	static StringView mime(StringView file_path) noexcept;
	static sys::ResourceLoader* loader(StringView mime) noexcept;

	static void add(sys::ResourceLoader* loader, StringView mime) noexcept;
	static void remove(StringView mime) noexcept;

	template<typename T>
	T* load(StringView file_path /* , ResourceType type = T::type() */) noexcept
	{
		return static_cast<T*>(load(file_path, T::type()));
	}

	template<typename T>
	Status load(T& t, StringView file_path /* , ResourceType type = T::type() */) noexcept
	{
		return load(static_cast<Resource&>(t), file_path, T::type());
	}

	Resource* load(StringView file_path, ResourceType type) noexcept;
	Status load(Resource& res, StringView file_path, ResourceType type) noexcept;
};

}

#endif  //  !__DK_RESOURCE_MANAGER_H__
