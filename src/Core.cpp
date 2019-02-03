#include "Log.h"
#include "Core.h"
#include "sys/Input.h"
#include "audio/Core.h"
#include "util/Perf.h"
#include "util/Ticker.h"
#include "sys/ResourceManager.h"
#include "sys/loaders/OBJ_Loader.h"
#include "sys/loaders/WAVE_Loader.h"
#include "sys/loaders/TextureLoader.h"

namespace dk
{

namespace
{

sys::WAVE_Loader   wave_loader;
sys::TextureLoader texture_loader;
sys::OBJ_Loader    obj_loader;

}

/* static */ bool            Core::s_running;
/* static */ graph::Renderer Core::s_active_renderer;

template<> /* static */ graph::Renderer* Core::active<graph::Renderer>() noexcept { return &s_active_renderer; }

/* static */ Status Core::run(Application* app) noexcept
{
	if (auto ret = app->create(); !ret)
		return ret;

	size_t count = 0;
	auto avr = std::chrono::microseconds::zero();
	auto next_time = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	util::Ticker clk(50);

	s_running = true;
	DK_LOG("Enter Core loop");
	while (s_running) {
		auto beg = std::chrono::high_resolution_clock::now();

		DK_PERF_MEASURE_BEG();
		DK_PERF_MEASURE(sys::Input::update());
		DK_PERF_MEASURE(app->update(0.0f));
		DK_PERF_MEASURE(app->render());
		DK_PERF_MEASURE_END();

		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		avr += diff;
		++count;

		if (end >= next_time) {
			auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>((end - next_time + std::chrono::seconds(1)));
			DK_LOG("FPS: ", count, " per ", elapsed_time.count() / 1000.0f, " ms, avr: ", avr.count() / 1000.0f / count, " ms");
			util::Perf::print();

			next_time = beg + std::chrono::seconds(1);
			avr = std::chrono::microseconds::zero();
			count = 0;
		}

		//  TODO: disable if bigger than VSync clk.wait();
	}

	DK_LOG("Exit from Core loop");
	app->destroy();
	return Status::OK;
}

/* static */ void Core::stop() noexcept
{
	s_running = false;
}

/* static */ Status Core::create() noexcept
{
	if (auto ret = Log::create(); !ret)
		return ret;

	if (auto ret = audio::Core::create(); !ret)
		return ret;

	if (auto ret = sys::Input::create(); !ret)
		return ret;

	/* std loaders */
	sys::ResourceManager::add(&wave_loader,    "wav");
	sys::ResourceManager::add(&texture_loader, "png");
	sys::ResourceManager::add(&texture_loader, "bmp");
	sys::ResourceManager::add(&texture_loader, "jpg");
	sys::ResourceManager::add(&texture_loader, "tga");
	sys::ResourceManager::add(&obj_loader,     "obj");

	DK_LOG_OK("Engine Core created");
	return Status::OK;
}

/* static */ void Core::destroy() noexcept
{
	audio::Core::destroy();
	DK_LOG_OK("Engine Core destroyed");
}

}
