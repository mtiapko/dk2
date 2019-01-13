#include "sys/resource_manager.h"
#include "containers/string.h"
#include "log.h"

namespace dk::sys
{

/* static */ hash_table<string_view, resource_loader*> resource_manager::s_loaders;

/* static */ resource* resource_manager::load(string_view file_path, resource_type type) noexcept
{
	auto ld = s_loaders.find(mime(file_path));
	if (ld == s_loaders.cend()) {
		DK_LOG_ERROR("Loader for file '", file_path, "' does not exist");
		return nullptr;
	}

	return ld->second->load(file_path, type);
}

/* static */ string_view resource_manager::mime(string_view file_path) noexcept
{
	auto dot_pos = file_path.rfind('.');
	if (dot_pos == string::npos)
		return {};

	++dot_pos;
	return { &file_path[dot_pos], file_path.size() - dot_pos };
}

/* static */ resource_loader* resource_manager::loader(string_view mime) noexcept
{
	auto ld = s_loaders.find(mime);
	if (ld != s_loaders.cend())
		return ld->second;

	return nullptr;
}

/* static */ void resource_manager::add(resource_loader* loader, string_view mime) noexcept
{
	s_loaders[mime] = loader;
}

/* static */ void resource_manager::remove(string_view mime) noexcept
{
	s_loaders.erase(mime);
}

}
