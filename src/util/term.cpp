#include "containers/string_view.h"
#include "log.h"

namespace dk::util
{

/* static */ void term::set(term_text_attrib attrib) noexcept
{
	switch (attrib) {
		case term_text_attrib::DEFAULT:  log::print(string_view("\033[0m")); break;
		case term_text_attrib::BOLD:     log::print(string_view("\033[1m")); break;
		case term_text_attrib::NOT_BOLD: log::print(string_view("\e[21m")); break;
		default:
			log::print("Error! Terminal does not support attribute: ", (uint32_t)attrib, '\n');
	}
}

/* static */ void term::set(term_text_color color) noexcept
{
	switch (color) {
		case term_text_color::DEFAULT:       log::print(string_view("\033[39m")); break;
		case term_text_color::BLACK:         log::print(string_view("\033[30m")); break;
		case term_text_color::RED:           log::print(string_view("\033[31m")); break;
		case term_text_color::GREEN:         log::print(string_view("\033[32m")); break;
		case term_text_color::YELLOW:        log::print(string_view("\033[33m")); break;
		case term_text_color::BLUE:          log::print(string_view("\033[34m")); break;
		case term_text_color::MAGENTA:       log::print(string_view("\033[35m")); break;
		case term_text_color::CYAN:          log::print(string_view("\033[36m")); break;
		case term_text_color::GRAY:          log::print(string_view("\033[90m")); break;
		case term_text_color::LIGHT_RED:     log::print(string_view("\033[91m")); break;
		case term_text_color::LIGHT_GREEN:   log::print(string_view("\033[92m")); break;
		case term_text_color::LIGHT_YELLOW:  log::print(string_view("\033[93m")); break;
		case term_text_color::LIGHT_BLUE:    log::print(string_view("\033[94m")); break;
		case term_text_color::LIGHT_MAGENTA: log::print(string_view("\033[95m")); break;
		case term_text_color::LIGHT_CYAN:    log::print(string_view("\033[96m")); break;
		case term_text_color::LIGHT_WHITE:   log::print(string_view("\033[97m")); break;
		case term_text_color::LIGHT_GRAY:    log::print(string_view("\033[37m")); break;
		default:
			log::print("Error! Terminal does not support text color: ", (uint32_t)color, '\n');
	}
}

/* static */ void term::set(term_back_color color) noexcept
{
	switch (color) {
		case term_back_color::DEFAULT:       log::print(string_view("\033[49m"));  break;
		case term_back_color::BLACK:         log::print(string_view("\033[40m"));  break;
		case term_back_color::RED:           log::print(string_view("\033[41m"));  break;
		case term_back_color::GREEN:         log::print(string_view("\033[42m"));  break;
		case term_back_color::YELLOW:        log::print(string_view("\033[43m"));  break;
		case term_back_color::BLUE:          log::print(string_view("\033[44m"));  break;
		case term_back_color::MAGENTA:       log::print(string_view("\033[45m"));  break;
		case term_back_color::CYAN:          log::print(string_view("\033[46m"));  break;
		case term_back_color::GRAY:          log::print(string_view("\033[100m")); break;
		case term_back_color::LIGHT_RED:     log::print(string_view("\033[101m")); break;
		case term_back_color::LIGHT_GREEN:   log::print(string_view("\033[102m")); break;
		case term_back_color::LIGHT_YELLOW:  log::print(string_view("\033[103m")); break;
		case term_back_color::LIGHT_BLUE:    log::print(string_view("\033[104m")); break;
		case term_back_color::LIGHT_MAGENTA: log::print(string_view("\033[105m")); break;
		case term_back_color::LIGHT_CYAN:    log::print(string_view("\033[106m")); break;
		case term_back_color::LIGHT_WHITE:   log::print(string_view("\033[107m")); break;
		case term_back_color::LIGHT_GRAY:    log::print(string_view("\033[47m"));  break;
		default:
			log::print("Error! Terminal does not support back color: ", (uint32_t)color, '\n');
	}
}

}
