#include "log.h"
#include "app.h"
#include "core.h"
#include "event_system.h"
#include "events/create_event.h"
#include "events/destroy_event.h"
#include "events/update_event.h"
#include "events/render_event.h"
#include "graphic/render_system.h"
#include "utils/clock.h"

namespace dk
{

render_system core::s_active_render_sys;

status core::run()
{
	struct : public event_listener<destroy_event>
	{
		bool is_running = true;
		void handle(const destroy_event&) override { is_running = false; }
	} app;

	event_system<destroy_event>::get().subscribe(&app);
	event_system<create_event>::get().send();

	clock clk(30);
	size_t count = 0;
	auto avr = std::chrono::microseconds::zero();
	auto& update_event_sys = event_system<update_event>::get();
	auto& render_event_sys = event_system<render_event>::get();
	while (app.is_running) {
		//  TODO: clk.is_elapsed()
		auto beg = std::chrono::high_resolution_clock::now();
		update_event_sys.send();
		render_event_sys.send();
		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		avr += diff;
		++count;

		DK_LOG("Frame time: ", diff.count() / 1000.0f, " ms, avr: ", avr.count() / 1000.0f / count, " ms");
		clk.wait();
	}

	DK_LOG("Exit from main loop");
	return status::OK;
}

status core::create()
{
	if (log::create() != status::OK)
		return status::ERROR;

	if (s_active_render_sys.create() != status::OK)
		return status::ERROR;

	return status::OK;
}

}
