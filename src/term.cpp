#include <cstdio>
#include "term.h"

namespace dk
{

void term::set(term_text_attrib attrib)
{
	switch (attrib) {
		case term_text_attrib::DEFAULT:  std::printf("\033[0m"); break;
		case term_text_attrib::BOLD:     std::printf("\033[1m"); break;
		case term_text_attrib::NOT_BOLD: std::printf("\e[21m"); break;
		default:
			std::printf("Error! Terminal does not support attribute: %u\n", (uint32_t)attrib);
	}
}

void term::set(term_text_color color)
{
	switch (color) {
		case term_text_color::DEFAULT:       std::printf("\033[39m"); break;
		case term_text_color::BLACK:         std::printf("\033[30m"); break;
		case term_text_color::RED:           std::printf("\033[31m"); break;
		case term_text_color::GREEN:         std::printf("\033[32m"); break;
		case term_text_color::YELLOW:        std::printf("\033[33m"); break;
		case term_text_color::BLUE:          std::printf("\033[34m"); break;
		case term_text_color::MAGENTA:       std::printf("\033[35m"); break;
		case term_text_color::CYAN:          std::printf("\033[36m"); break;
		case term_text_color::GRAY:          std::printf("\033[90m"); break;
		case term_text_color::LIGHT_RED:     std::printf("\033[91m"); break;
		case term_text_color::LIGHT_GREEN:   std::printf("\033[92m"); break;
		case term_text_color::LIGHT_YELLOW:  std::printf("\033[93m"); break;
		case term_text_color::LIGHT_BLUE:    std::printf("\033[94m"); break;
		case term_text_color::LIGHT_MAGENTA: std::printf("\033[95m"); break;
		case term_text_color::LIGHT_CYAN:    std::printf("\033[96m"); break;
		case term_text_color::LIGHT_WHITE:   std::printf("\033[97m"); break;
		case term_text_color::LIGHT_GRAY:    std::printf("\033[37m"); break;
		default:
			std::printf("Error! Terminal does not support text color: %u\n", (uint32_t)color);
	}
}

void term::set(term_back_color color)
{
	switch (color) {
		case term_back_color::DEFAULT:       std::printf("\033[49m");  break;
		case term_back_color::BLACK:         std::printf("\033[40m");  break;
		case term_back_color::RED:           std::printf("\033[41m");  break;
		case term_back_color::GREEN:         std::printf("\033[42m");  break;
		case term_back_color::YELLOW:        std::printf("\033[43m");  break;
		case term_back_color::BLUE:          std::printf("\033[44m");  break;
		case term_back_color::MAGENTA:       std::printf("\033[45m");  break;
		case term_back_color::CYAN:          std::printf("\033[46m");  break;
		case term_back_color::GRAY:          std::printf("\033[100m"); break;
		case term_back_color::LIGHT_RED:     std::printf("\033[101m"); break;
		case term_back_color::LIGHT_GREEN:   std::printf("\033[102m"); break;
		case term_back_color::LIGHT_YELLOW:  std::printf("\033[103m"); break;
		case term_back_color::LIGHT_BLUE:    std::printf("\033[104m"); break;
		case term_back_color::LIGHT_MAGENTA: std::printf("\033[105m"); break;
		case term_back_color::LIGHT_CYAN:    std::printf("\033[106m"); break;
		case term_back_color::LIGHT_WHITE:   std::printf("\033[107m"); break;
		case term_back_color::LIGHT_GRAY:    std::printf("\033[47m");  break;
		default:
			std::printf("Error! Terminal does not support back color: %u\n", (uint32_t)color);
	}
}

}
