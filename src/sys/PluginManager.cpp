#include "dk/sys/PluginManager.h"
#include "dk/Core.h"
#include "dk/Log.h"

namespace dk::sys
{

/* static */ void PluginManager::unload_plugin(Plugin* plugin, os::DynamicLib& lib) noexcept
{
	auto dk_plugin_close = lib.load_func<void ()>("dk_plugin_close");
	if (dk_plugin_close != nullptr) // XXX: keep it optional? or error?
		dk_plugin_close();

	plugin->destroy();
	DK_LOG("Plugin '", plugin->name(), "' unloaded");
}

Plugin* PluginManager::load(StringView path) noexcept
{
	os::DynamicLib lib;
	if (!lib.load(String("bin/") + String(path))) // TODO: remove before release
		return nullptr;

	auto dk_plugin_open = lib.load_func<Plugin* ()>("dk_plugin_open");
	if (dk_plugin_open == nullptr)
		return nullptr;

	auto plugin = dk_plugin_open();
	if (plugin == nullptr) {
		DK_LOG_ERROR("Failed to load plugin '", path, '\'');
		return nullptr;
	}

	DK_LOG("Loading plugin '", plugin->name(), '\'');
	if (!plugin->create())
		return nullptr;

	DK_LOG_OK("Plugin '", plugin->name(), "' loaded");
	m_plugins.emplace_back(plugin, std::move(lib));
	return plugin;
}

void PluginManager::unload(Plugin* plugin) noexcept
{
	auto size = m_plugins.size();
	std::erase_if(m_plugins, [desired = plugin](auto& pair) {
		auto& [plugin, lib] = pair;
		if (plugin != desired)
			return false;

		unload_plugin(plugin, lib);
		return true;
	});

	// XXX: possible null or bad pointer dereference
	if (size == m_plugins.size())
		DK_LOG_WARNING("Plugin '", plugin->name(), "' loaded not by plugin manager");
}

Status PluginManager::create() noexcept
{
	return Status::OK;
}

void PluginManager::destroy() noexcept
{
	for (auto& [plugin, lib]: m_plugins)
		unload_plugin(plugin, lib);

	m_plugins.clear();
}

}
