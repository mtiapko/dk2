#ifndef __DK_PERF_H__
#define __DK_PERF_H__

#include "util/PerfEntity.h"
#include "containers/HashTable.h"

#define DK_PERF_MEASURE_BEG() util::Perf::measure_beg()
#define DK_PERF_MEASURE_END() util::Perf::measure_end()

#define DK_PERF_MEASURE(exec) \
	[&](StringView func) { \
		auto __perf_beg = std::chrono::high_resolution_clock::now(); \
		exec; \
		auto __perf_end = std::chrono::high_resolution_clock::now(); \
		auto& __perf_e = util::Perf::get(func, __LINE__); \
		__perf_e.exec_func = #exec; \
		__perf_e.exec_duration = std::chrono::duration_cast<std::chrono::microseconds>(__perf_end - __perf_beg); \
		++__perf_e.exec_count; \
	}(__PRETTY_FUNCTION__)

namespace std
{
	template<> struct hash<dk::util::PerfEntityLocation> {
		std::size_t operator()(const dk::util::PerfEntityLocation &loc) const {
			return std::hash<dk::StringView>{}(loc.func);
		}
	};
}

namespace dk::util
{

class Perf
{
private:
	static inline HashTable<PerfEntityLocation, PerfEntity> s_entities;
	static inline std::chrono::high_resolution_clock::time_point s_beg;
	static inline std::chrono::high_resolution_clock::time_point s_end;

public:
	static PerfEntity& get(StringView func, size_t line) noexcept { return s_entities[PerfEntityLocation{ func, line }]; }

	static void measure_beg() noexcept { s_beg = std::chrono::high_resolution_clock::now(); }
	static void measure_end() noexcept { s_end = std::chrono::high_resolution_clock::now(); }

	static void stop() noexcept;

	static void print() noexcept;
};

}

#endif  //  !__DK_PERF_H__
