#ifndef __DK_SYS_RESOURCE_MANAGER_H__
#define __DK_SYS_RESOURCE_MANAGER_H__

#include "dk/containers/HashTable.h"
#include "dk/containers/String.h"
#include "dk/containers/Vector.h"
#include "dk/containers/Pair.h"
#include "dk/sys/ResourceImporter.h"
#include "dk/sys/ResourceExporter.h"

namespace dk::sys
{

class ResourceManager
{
private:
	HashTable<String, Vector<Pair<ResourceType, ResourceImporter*>>> m_importers;
	HashTable<String, Vector<Pair<ResourceType, ResourceExporter*>>> m_exporters;
	HashTable<String, Resource*> m_import_cache;

public:
	static StringView mime(StringView file_path) noexcept;

	// TODO: add 'set' methods
	bool is_cache_resource_enabled() const noexcept { return true; }
	bool is_save_resource_data_enabled() const noexcept { return true; }

	ResourceImporter* importer(StringView mime, ResourceType type) const noexcept;
	Status add_importer(StringView mime, ResourceType type, ResourceImporter* importer) noexcept;
	Status remove_importer(StringView mime) noexcept;

	ResourceExporter* exporter(StringView mime, ResourceType type) const noexcept;
	Status add_exporter(StringView mime, ResourceType type, ResourceExporter* exporter) noexcept;
	Status remove_exporter(StringView mime) noexcept;

	template<typename T>
	T* import(StringView file_path) noexcept
	{
		return (T*)this->import(T::get_resource_type(), file_path);
	}

	Resource* import(ResourceType type, StringView file_path) noexcept;
	Status import(Resource* res, StringView file_path) noexcept;

	void delete_resource(Resource* res) const noexcept
	{
		// TODO: if res does not call this method it is still in cache
		res->resource_creator()->delete_resource(res);
	}
};

}

#endif // !__DK_SYS_RESOURCE_MANAGER_H__
