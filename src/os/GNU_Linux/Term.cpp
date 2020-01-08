#include "dk/containers/StringView.h"
#include "dk/Log.h"

namespace dk::os
{

/* static */ void Term::set(TermTextAttrib attrib) noexcept
{
	switch (attrib) {
		case TermTextAttrib::DEFAULT:  Log::print(StringView("\033[0m")); break;
		case TermTextAttrib::BOLD:     Log::print(StringView("\033[1m")); break;
		case TermTextAttrib::NOT_BOLD: Log::print(StringView("\e[21m")); break;
		default:
			Log::print("Error! Terminal does not support attribute: ", (uint32_t)attrib, '\n');
	}
}

/* static */ void Term::set(TermTextColor color) noexcept
{
	switch (color) {
		case TermTextColor::DEFAULT:       Log::print(StringView("\033[39m")); break;
		case TermTextColor::BLACK:         Log::print(StringView("\033[30m")); break;
		case TermTextColor::RED:           Log::print(StringView("\033[31m")); break;
		case TermTextColor::GREEN:         Log::print(StringView("\033[32m")); break;
		case TermTextColor::YELLOW:        Log::print(StringView("\033[33m")); break;
		case TermTextColor::BLUE:          Log::print(StringView("\033[34m")); break;
		case TermTextColor::MAGENTA:       Log::print(StringView("\033[35m")); break;
		case TermTextColor::CYAN:          Log::print(StringView("\033[36m")); break;
		case TermTextColor::GRAY:          Log::print(StringView("\033[90m")); break;
		case TermTextColor::LIGHT_RED:     Log::print(StringView("\033[91m")); break;
		case TermTextColor::LIGHT_GREEN:   Log::print(StringView("\033[92m")); break;
		case TermTextColor::LIGHT_YELLOW:  Log::print(StringView("\033[93m")); break;
		case TermTextColor::LIGHT_BLUE:    Log::print(StringView("\033[94m")); break;
		case TermTextColor::LIGHT_MAGENTA: Log::print(StringView("\033[95m")); break;
		case TermTextColor::LIGHT_CYAN:    Log::print(StringView("\033[96m")); break;
		case TermTextColor::LIGHT_WHITE:   Log::print(StringView("\033[97m")); break;
		case TermTextColor::LIGHT_GRAY:    Log::print(StringView("\033[37m")); break;
		default:
			Log::print("Error! Terminal does not support text color: ", (uint32_t)color, '\n');
	}
}

/* static */ void Term::set(TermBackColor color) noexcept
{
	switch (color) {
		case TermBackColor::DEFAULT:       Log::print(StringView("\033[49m"));  break;
		case TermBackColor::BLACK:         Log::print(StringView("\033[40m"));  break;
		case TermBackColor::RED:           Log::print(StringView("\033[41m"));  break;
		case TermBackColor::GREEN:         Log::print(StringView("\033[42m"));  break;
		case TermBackColor::YELLOW:        Log::print(StringView("\033[43m"));  break;
		case TermBackColor::BLUE:          Log::print(StringView("\033[44m"));  break;
		case TermBackColor::MAGENTA:       Log::print(StringView("\033[45m"));  break;
		case TermBackColor::CYAN:          Log::print(StringView("\033[46m"));  break;
		case TermBackColor::GRAY:          Log::print(StringView("\033[100m")); break;
		case TermBackColor::LIGHT_RED:     Log::print(StringView("\033[101m")); break;
		case TermBackColor::LIGHT_GREEN:   Log::print(StringView("\033[102m")); break;
		case TermBackColor::LIGHT_YELLOW:  Log::print(StringView("\033[103m")); break;
		case TermBackColor::LIGHT_BLUE:    Log::print(StringView("\033[104m")); break;
		case TermBackColor::LIGHT_MAGENTA: Log::print(StringView("\033[105m")); break;
		case TermBackColor::LIGHT_CYAN:    Log::print(StringView("\033[106m")); break;
		case TermBackColor::LIGHT_WHITE:   Log::print(StringView("\033[107m")); break;
		case TermBackColor::LIGHT_GRAY:    Log::print(StringView("\033[47m"));  break;
		default:
			Log::print("Error! Terminal does not support back color: ", (uint32_t)color, '\n');
	}
}

}
