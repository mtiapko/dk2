#ifndef __DK_SYS_PLUGIN_MANAGER_H__
#define __DK_SYS_PLUGIN_MANAGER_H__

#include "dk/containers/Vector.h"
#include "dk/containers/String.h"
#include "dk/containers/Pair.h"
#include "dk/sys/Plugin.h"
#include "dk/os/DynamicLib.h"

namespace dk::sys
{

class PluginManager
{
private:
	static void unload_plugin(Plugin* plugin, os::DynamicLib& lib) noexcept;

	Vector<Pair<Plugin*, os::DynamicLib>> m_plugins;

public:
	Plugin* load(StringView path) noexcept;
	void unload(Plugin* plugin) noexcept;

	Status create() noexcept;
	void destroy() noexcept;
};

}

#endif // !__DK_SYS_PLUGIN_MANAGER_H__
