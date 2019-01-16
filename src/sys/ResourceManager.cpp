#include "sys/ResourceManager.h"
#include "containers/String.h"
#include "Log.h"

namespace dk::sys
{

/* static */ HashTable<StringView, ResourceLoader*> ResourceManager::s_loaders;

/* static */ Resource* ResourceManager::load(StringView file_path, ResourceType type) noexcept
{
	auto ld = s_loaders.find(mime(file_path));
	if (ld == s_loaders.cend()) {
		DK_LOG_ERROR("Loader for file '", file_path, "' does not exist");
		return nullptr;
	}

	return ld->second->load(file_path, type);
}

/* static */ Status ResourceManager::load(Resource& res, StringView file_path, ResourceType type) noexcept
{
	auto ld = s_loaders.find(mime(file_path));
	if (ld == s_loaders.cend()) {
		DK_LOG_ERROR("Loader for file '", file_path, "' does not exist");
		return Status::ERROR;
	}

	return ld->second->load(res, file_path, type);
}

/* static */ StringView ResourceManager::mime(StringView file_path) noexcept
{
	auto dot_pos = file_path.rfind('.');
	if (dot_pos == String::npos)
		return {};

	++dot_pos;
	return { &file_path[dot_pos], file_path.size() - dot_pos };
}

/* static */ ResourceLoader* ResourceManager::loader(StringView mime) noexcept
{
	auto ld = s_loaders.find(mime);
	if (ld != s_loaders.cend())
		return ld->second;

	return nullptr;
}

/* static */ void ResourceManager::add(ResourceLoader* loader, StringView mime) noexcept
{
	s_loaders[mime] = loader;
}

/* static */ void ResourceManager::remove(StringView mime) noexcept
{
	s_loaders.erase(mime);
}

}
