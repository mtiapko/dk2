#ifndef __DK_LOG_H__
#define __DK_LOG_H__

#include <chrono>
#include <iomanip>
#include <iostream>
#include "dk/os/Term.h"
#include "dk/Status.h"

#define DK_LOG_PRINT(...) dk::Log::print(__VA_ARGS__, '\n')

#define DK_LOG_COLOR(color, ...) \
	dk::os::TermTextColor::color, dk::os::TermTextAttrib::BOLD, \
	__VA_ARGS__, \
	dk::os::TermTextAttrib::DEFAULT

#define DK_LOG_BLANK_HEADER "[       ]"
#define DK_LOG_HEADER(color, title, file, func, line) \
	"[", DK_LOG_COLOR(color, title), "] ", \
	DK_LOG_COLOR(GRAY, std::setw(9), dk::LogTimestamp{}, " - ", file, "::", func, " (", line, ") - ")

#define DK_LOG_TITLE(color, title, file, func, line, ...) \
	dk::Log::print(DK_LOG_HEADER(color, title, file, func, line), __VA_ARGS__)

#define DK_LOG_IMPL(file, func, line, ...)         DK_LOG_TITLE(LIGHT_BLUE,   "  MSG  ", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_OK_IMPL(file, func, line, ...)      DK_LOG_TITLE(LIGHT_GREEN,  "  OK!  ", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_WARNING_IMPL(file, func, line, ...) DK_LOG_TITLE(LIGHT_YELLOW, "WARNING", file, func, line, __VA_ARGS__, '\n')
#define DK_LOG_ERROR_IMPL(file, func, line, ...)   DK_LOG_TITLE(LIGHT_RED,    " ERROR ", file, func, line, __VA_ARGS__, '\n')

#define DK_LOG(...)         DK_LOG_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_OK(...)      DK_LOG_OK_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_WARNING(...) DK_LOG_WARNING_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define DK_LOG_ERROR(...)   DK_LOG_ERROR_IMPL(__FILE__, __func__, __LINE__, __VA_ARGS__)

namespace dk
{

struct LogTimestamp {};

class Log
{
private:
	static inline std::chrono::steady_clock::time_point s_start; // TODO: inline with plugins? will be 2 instances???

public:
	template<typename T> Log operator<<(const T& t) const noexcept { std::clog << t; return {}; }
	Log operator<<(os::TermTextAttrib attrib) const noexcept { os::Term::set(attrib); return {}; }
	Log operator<<(os::TermTextColor color) const noexcept { os::Term::set(color); return {}; }
	Log operator<<(os::TermBackColor color) const noexcept { os::Term::set(color); return {}; }

	Log operator<<(LogTimestamp) const noexcept {
		auto now = std::chrono::steady_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(now - s_start).count();
		std::clog << dur / 1000.0f << " ms";
		return {};
	}

	template<typename... Args> static void print(const Args&... args) noexcept { (Log{} << ... << args); }

	static Status create() noexcept
	{
		s_start = std::chrono::steady_clock::now();
		return Status::OK;
	}
};

}

#endif // !__DK_LOG_H__
