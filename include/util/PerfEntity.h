#ifndef __DK_UTIL_PERF_ENTITY_H__
#define __DK_UTIL_PERF_ENTITY_H__

#include <chrono>
#include "containers/StringView.h"

namespace dk::util
{

struct PerfEntityLocation
{
	StringView func;
	size_t     line;

	bool operator==(const PerfEntityLocation &that) const noexcept { return func == that.func && line == that.line; }
};

struct PerfEntity
{
	StringView                                   exec_func;
	std::chrono::high_resolution_clock::duration exec_duration;
	size_t                                       exec_count;
};

}

#endif  //  !__DK_UTIL_PERF_ENTITY_H__
