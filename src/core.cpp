#include "log.h"
#include "core.h"
#include "util/ticker.h"
#include "sys/event_manager.h"
#include "sys/events/update_event.h"
#include "sys/events/render_event.h"

namespace dk
{

sys::renderer core::s_active_renderer;

template<> sys::renderer* core::active<sys::renderer>() noexcept { return &s_active_renderer; }

status core::run() noexcept
{
	size_t count = 0;
	auto avr = std::chrono::microseconds::zero();
	auto& update_event_mgr = sys::event_manager<sys::update_event>::get();
	auto& render_event_mgr = sys::event_manager<sys::render_event>::get();

	util::ticker clk(30);
	while (true) {
		auto beg = std::chrono::high_resolution_clock::now();
		update_event_mgr.send(0.0f);
		render_event_mgr.send();
		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		avr += diff;
		++count;

		DK_LOG("Frame time: ", diff.count() / 1000.0f, " ms, avr: ", avr.count() / 1000.0f / count, " ms");
		clk.wait();
	}

	DK_LOG("Exit from core loop");
	return status::OK;
}

status core::create() noexcept
{
	if (auto res = log::create(); !res)
		return res;

	return status::OK;
}

}
