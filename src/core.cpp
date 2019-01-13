#include "log.h"
#include "core.h"
#include "sys/input.h"
#include "audio/core.h"
#include "util/ticker.h"
#include "sys/resource_manager.h"
#include "sys/loaders/wave_loader.h"

namespace dk
{

namespace
{

sys::wave_loader wave_loader;

}

/* static */ bool            core::s_running;
/* static */ graph::renderer core::s_active_renderer;

template<> /* static */ graph::renderer* core::active<graph::renderer>() noexcept { return &s_active_renderer; }

/* static */ status core::run(application* app) noexcept
{
	if (auto ret = app->create(); !ret)
		return ret;

	size_t count = 0;
	auto avr = std::chrono::microseconds::zero();
	auto next_time = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	util::ticker clk(30);

	s_running = true;
	DK_LOG("Enter core loop");
	while (s_running) {
		auto beg = std::chrono::high_resolution_clock::now();

		sys::input::update();
		app->update(0.0f);
		app->render();

		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		avr += diff;
		++count;

		if (end >= next_time) {
			auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>((end - next_time + std::chrono::seconds(1)));
			DK_LOG("FPS: ", count, " per ", elapsed_time.count() / 1000.0f, " ms, avr: ", avr.count() / 1000.0f / count, " ms");
			next_time = beg + std::chrono::seconds(1);
			avr = std::chrono::microseconds::zero();
			count = 0;
		}

		clk.wait();
	}

	DK_LOG("Exit from core loop");
	app->destroy();
	return status::OK;
}

/* static */ void core::stop() noexcept
{
	s_running = false;
}

/* static */ status core::create() noexcept
{
	if (auto ret = log::create(); !ret)
		return ret;

	if (auto ret = audio::core::create(); !ret)
		return ret;

	if (auto ret = sys::input::create(); !ret)
		return ret;

	/* std loaders */
	sys::resource_manager::add(&wave_loader, "wav");

	DK_LOG_OK("Engine core created");
	return status::OK;
}

/* static */ void core::destroy() noexcept
{
	audio::core::destroy();
	DK_LOG_OK("Engine core destroyed");
}

}
