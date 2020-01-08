#include "dk/sys/ResourceManager.h"
#include "dk/Log.h"

namespace dk::sys
{

/* static */ StringView ResourceManager::mime(StringView file_path) noexcept
{
	auto dot_pos = file_path.rfind('.');
	if (dot_pos == StringView::npos)
		return {};

	++dot_pos;
	return { &file_path[dot_pos], file_path.size() - dot_pos };
}

ResourceImporter* ResourceManager::importer(StringView mime, ResourceType type) const noexcept
{
	auto vec = m_importers.find(String(mime));
	if (vec == m_importers.cend()) {
		DK_LOG_ERROR("Resource importer for '", mime, "' does not exist");
		return nullptr;
	}

	auto pair = std::find_if(vec->second.begin(), vec->second.end(), [type](const auto& pair) noexcept
		{ return type == pair.first; }
	);

	if (pair == vec->second.end()) {
		DK_LOG_ERROR("Resource importer for '", mime, "' and type '", ResourceTypeNames[(int)type], "' does not exist");
		return nullptr;
	}

	return pair->second;
}

Status ResourceManager::add_importer(StringView mime, ResourceType type, ResourceImporter* importer) noexcept
{
	auto [iter, is_inserted] = m_importers.try_emplace(String(mime));
	if (std::find_if(iter->second.begin(), iter->second.end(), [type](const auto& pair) noexcept
			{ return type == pair.first; }) != iter->second.end())
		DK_LOG_WARNING("Resource importer for '", mime, "' and type '", ResourceTypeNames[(int)type], "' already exists");

	iter->second.emplace_back(type, importer);
	DK_LOG_OK("Resource importer for '", mime, "' and type '", ResourceTypeNames[(int)type], "' successfully added");
	return Status::OK;
}

Resource* ResourceManager::import(ResourceType type, StringView file_path) noexcept
{
	auto import_cache = m_import_cache.find(String(file_path));
	if (import_cache != m_import_cache.end()) {
		DK_LOG("Resource '", file_path, "' imported from cache");
		return import_cache->second;
	}

	auto importer = this->importer(mime(file_path), type);
	if (importer == nullptr) {
		DK_LOG_ERROR("File '", file_path, "' not imported");
		return nullptr;
	}

	auto res = importer->import(type, file_path);
	m_import_cache.emplace(file_path, res);
	return res;
}

Status ResourceManager::import(Resource* res, StringView file_path) noexcept
{
	auto importer = this->importer(mime(file_path), res->resource_type());
	if (importer == nullptr) {
		DK_LOG_ERROR("File '", file_path, "' not imported");
		return Status::ERROR;
	}

	// TODO: remove res for old path and add for new
	m_import_cache.emplace(file_path, res);
	return importer->import(res, file_path);
}

}
