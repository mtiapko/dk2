#ifndef __DK_LOG_H__
#define __DK_LOG_H__

#include <iostream>
#include "term.h"

#define DK_LOG_HEADER(title) "[" title "] " __FILE__ "::", __func__, " (", __LINE__, ") - "
#define DK_LOG_PRINT(title, ...) dk::log::print(DK_LOG_HEADER(title), __VA_ARGS__)

#define DK_LOG(...)     DK_LOG_PRINT("  MSG  ", __VA_ARGS__, '\n');
#define DK_LOG_WARNING(...) DK_LOG_PRINT("WARNING", __VA_ARGS__, '\n');
#define DK_LOG_ERROR(...)   DK_LOG_PRINT(" ERROR ", __VA_ARGS__, '\n');

namespace dk
{

class log
{
public:
	template<typename T> log operator<<(const T& t) { std::clog << t; return {}; }
	log operator<<(term_text_attrib attrib) { term::set(attrib); return {}; }
	log operator<<(term_text_color color) { term::set(color); return {}; }
	log operator<<(term_back_color color) { term::set(color); return {}; }

	template<typename... Args> static void print(const Args&... args) { (log{} << ... << args); }
};

}

#endif  //  !__DK_LOG_H__
