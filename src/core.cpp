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

ret_code core::run()
{
	if (s_app->create() != ret_code::OK)
		return ret_code::ERROR;

	clock clk(5);
	s_running = true;
	while (s_running) {
		//  TODO: clk.is_elapsed()
		auto beg = std::chrono::high_resolution_clock::now();
		s_app->update();
		s_app->render();
		auto end = std::chrono::high_resolution_clock::now();

		DK_LOG("Frame time: ", std::chrono::duration_cast<std::chrono::microseconds>(end - beg).count() / 1000.0f, " ms");
		clk.wait();
	}

	DK_LOG("Exit from main loop");
	return ret_code::OK;
}

ret_code core::create(application* app)
{
	s_app = app;
	if (log::create() != ret_code::OK)
		return ret_code::ERROR;

	if (s_active_render_sys.create() != ret_code::OK)
		return ret_code::ERROR;

	return ret_code::OK;
}

}
