#ifndef __DK_CORE_H__
#define __DK_CORE_H__

#include "dk/graph/Renderer.h"
#include "dk/sys/ResourceManager.h"
#include "dk/sys/PluginManager.h"
#include "dk/Application.h"

namespace dk
{

class Core
{
private:
	bool m_is_created = false;
	bool m_is_running = false;

	sys::ResourceManager m_resource_manager;
	sys::PluginManager   m_plugin_manager;
	graph::Renderer*     m_active_renderer = nullptr;

	Core() = default;

public:
	Core(const Core&) = delete;

	static Core& get() noexcept
	{
		static Core inst;
		return inst;
	}

	sys::ResourceManager& resource_manager() noexcept
	{
		return m_resource_manager;
	}

	sys::PluginManager& plugin_manager() noexcept
	{
		return m_plugin_manager;
	}

	template<typename T> Status set_active(T* t) noexcept;
	template<typename T> T* active() noexcept;

	Status run(Application* app) noexcept;
	void stop() noexcept { m_is_running = false; }

	Status create() noexcept;
	void destroy() noexcept;
};

}

#endif // !__DK_CORE_H__
