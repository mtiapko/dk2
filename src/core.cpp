#include "log.h"
#include "core.h"
#include "sys/input.h"
#include "util/ticker.h"

namespace dk
{

/* static */ graph::renderer core::s_active_renderer;

template<> graph::renderer* core::active<graph::renderer>() noexcept { return &s_active_renderer; }

status core::run(application* app) noexcept
{
	if (auto res = app->create(); !res)
		return res;

	size_t count = 0;
	auto avr = std::chrono::microseconds::zero();
	util::ticker clk(30);
	while (true) {
		auto beg = std::chrono::high_resolution_clock::now();

		sys::input::update();
		app->update(0.0f);
		app->render();

		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		avr += diff;
		++count;

		DK_LOG("Frame time: ", diff.count() / 1000.0f, " ms, avr: ", avr.count() / 1000.0f / count, " ms");
		clk.wait();
	}

	app->destroy();
	DK_LOG("Exit from core loop");
	return status::OK;
}

status core::create() noexcept
{
	if (auto res = log::create(); !res)
		return res;

	if (auto res = sys::input::create(); !res)
		return res;

	return status::OK;
}

}
