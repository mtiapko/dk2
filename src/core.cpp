#include "log.h"
#include "app.h"
#include "core.h"
#include "utils/clock.h"
#include "graphic/render_system.h"

namespace dk
{

bool          core::s_running;
render_system core::s_active_render_sys;
application*  core::s_app;

status core::run()
{
	if (s_app->create() != status::OK)
		return status::ERROR;

	clock clk(5);
	s_running = true;
	auto avr = std::chrono::microseconds::zero();
	size_t count = 0;
	while (s_running) {
		//  TODO: clk.is_elapsed()
		auto beg = std::chrono::high_resolution_clock::now();
		s_app->update();
		s_app->render();
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

status core::create(application* app)
{
	s_app = app;
	if (log::create() != status::OK)
		return status::ERROR;

	if (s_active_render_sys.create() != status::OK)
		return status::ERROR;

	return status::OK;
}

}
