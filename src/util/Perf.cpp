#include "Log.h"
#include "util/Perf.h"

namespace dk::util
{

/* static */ void Perf::print() noexcept
{
	float duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(s_end - s_beg).count() / 1000.0f;
	DK_LOG("Performance measurement duration: ", duration_ms, " ms");

	for (auto& [loc, e]: s_entities) {
		auto exec_duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(e.exec_duration).count() / 1000.0f;
		DK_LOG_IMPL("<file>", loc.func, loc.line,
				"exec: '", e.exec_func, "', "
				"count: ", e.exec_count, ", "
				"avr: ", exec_duration_ms, " ms (", exec_duration_ms / duration_ms * 100.0f, "%)");

		e.exec_duration = decltype(e.exec_duration)::zero();
		e.exec_count = 0;
	}
}

}
