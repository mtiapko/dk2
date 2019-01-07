#ifndef __DK_LOG_H__
#define __DK_LOG_H__

#include <chrono>
#include <iomanip>
#include <iostream>
#include "status.h"
#include "util/term.h"

#define DK_LOG_COLOR(color, ...) \
	dk::util::term_text_color::color, dk::util::term_text_attrib::BOLD, \
	__VA_ARGS__, \
	dk::util::term_text_attrib::DEFAULT

#define DK_LOG_HEADER(color, title, file, func, line) \
	"[", DK_LOG_COLOR(color, title), "] ", \
	DK_LOG_COLOR(GRAY, dk::log_timestamp{}, " - ", file, "::", func, " (", line, ") - ")

#define DK_LOG_PRINT(color, title, file, func, line, ...) \
	dk::log::print(DK_LOG_HEADER(color, title, file, func, line), __VA_ARGS__)

#define DK_LOG_IMPL(file, func, line, ...)         DK_LOG_PRINT(LIGHT_BLUE,   "  MSG  ", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_OK_IMPL(file, func, line, ...)      DK_LOG_PRINT(LIGHT_GREEN,  "  OK!  ", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_WARNING_IMPL(file, func, line, ...) DK_LOG_PRINT(LIGHT_YELLOW, "WARNING", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_ERROR_IMPL(file, func, line, ...)   DK_LOG_PRINT(LIGHT_RED,    " ERROR ", file, func, line, __VA_ARGS__, '\n')

#define DK_LOG(...)         DK_LOG_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_OK(...)      DK_LOG_OK_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_WARNING(...) DK_LOG_WARNING_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_ERROR(...)   DK_LOG_ERROR_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)

namespace dk
{

struct log_timestamp {};

class log
{
private:
	static inline std::chrono::steady_clock::time_point s_start;  //  TODO: inline with plugins? will be 2 instances???

public:
	template<typename T> log operator<<(const T& t) const noexcept { std::clog << t; return {}; }
	log operator<<(util::term_text_attrib attrib) const noexcept { util::term::set(attrib); return {}; }
	log operator<<(util::term_text_color color) const noexcept { util::term::set(color); return {}; }
	log operator<<(util::term_back_color color) const noexcept { util::term::set(color); return {}; }

	log operator<<(log_timestamp) const noexcept {
		auto now = std::chrono::steady_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(now - s_start).count();
		std::clog << dur / 1000.0f << " ms";
		return {};
	}

	template<typename... Args> static void print(const Args&... args) noexcept { (log{} << ... << args); }

	static status create() noexcept
	{
		s_start = std::chrono::steady_clock::now();
		return status::OK;
	}
};

}

#endif  //  !__DK_LOG_H__
