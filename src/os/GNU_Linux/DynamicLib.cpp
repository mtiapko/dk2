#include "dk/os/DynamicLib.h"
#include "dk/Log.h"

namespace dk::os
{

void* DynamicLib::load_func_impl(const String& name) const noexcept
{
	auto ptr = dlsym(m_lib.get(), name.data());
	if (ptr == nullptr) { // XXX: dlsym could return NULL on success, but who cares?
		DK_LOG_ERROR("Failed to find function '", name, "' in dynamic lib ", dlerror());
		return nullptr;
	}

	return ptr;
}

Status DynamicLib::load(StringView path) noexcept
{
	m_path = path;
	m_lib.reset(dlopen(m_path.data(), RTLD_NOW));
	if (!m_lib) {
		DK_LOG_ERROR("Failed to open dynamic lib ", dlerror());
		return Status::ERROR;
	}

	return Status::OK;
}

}
