#include <chrono>
#include <atomic>
#include <thread>
#include "dk/sys/Input.h"
#include "dk/os/Descriptor.h"
#include "dk/Core.h"
#include "dk/Log.h"

namespace dk
{

template<>
Status Core::set_active(graph::Renderer* renderer) noexcept
{
	m_active_renderer = renderer;
	return Status::OK;
}

template<>
graph::Renderer* Core::active() noexcept
{
	return m_active_renderer;
}

/* static */ Status Core::run(Application* app) noexcept
{
	if (auto err = app->create(); !err)
		return err;

	DK_LOG("Enter Core loop");
	const auto update_period = std::chrono::high_resolution_clock::duration(std::chrono::seconds(1)) / 60;
	auto beg_time = std::chrono::high_resolution_clock::now();
	auto next_update_time = beg_time; // TODO: rethink '+ update_period'
	//auto next_print_time = beg_time + std::chrono::seconds(1);

	std::atomic<int> fps = 0;
	std::atomic<int> ups = 0;

	std::thread fps_counter([](std::atomic<int>& fps, std::atomic<int>& ups, bool& m_is_running) noexcept {
		while (true) {
			if (!m_is_running)
				return;

			auto beg_time = std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			auto end_time = std::chrono::high_resolution_clock::now();

			auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - beg_time).count()
				/ 1000.0f;
			DK_LOG(
				"FPS: ", fps, " (", elapsed_time / fps, " ms), "
				"UPS: ", ups, " (", elapsed_time / ups, " ms), "
				"per ", elapsed_time, " ms"
			);

			fps = 0;
			ups = 0;
		}
	}, std::ref(fps), std::ref(ups), std::ref(m_is_running));

	m_is_running = true;
	while (m_is_running) {
		while (std::chrono::high_resolution_clock::now() >= next_update_time) {
			next_update_time += update_period;
			app->update();
			++ups;
		}

		app->render();
		++fps;

		/*auto end_time = std::chrono::high_resolution_clock::now();
		if (end_time >= next_print_time) {
			auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - beg_time).count()
				/ 1000.0f;
			DK_LOG(
				"FPS: ", fps, " (", elapsed_time / fps, " ms), "
				"UPS: ", ups, " (", elapsed_time / ups, " ms), "
				"per ", elapsed_time, " ms"
			);

			beg_time = std::chrono::high_resolution_clock::now();
			next_print_time = beg_time + std::chrono::seconds(1);
			fps = 0;
			ups = 0;
		}*/
	}

	fps_counter.join();
	app->destroy();
	DK_LOG("Exit from Core loop");
	return Status::OK;
}

/* static */ Status Core::create() noexcept
{
	if (auto err = Log::create(); !err)
		return err;

	if (auto err = os::Descriptor::create(); !err)
		return err;

	if (auto err = sys::Keyboard::create(); !err)
		return err;

	if (auto err = sys::Input::create(); !err)
		return err;

	if (auto err = m_plugin_manager.create(); !err)
		return err;

	m_is_created = true;
	return Status::OK;
}

/* static */ void Core::destroy() noexcept
{
	m_plugin_manager.destroy();
	m_active_renderer = nullptr;
	m_is_created = false;
}

}
