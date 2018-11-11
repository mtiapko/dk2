#ifndef __DK_TERM_H__
#define __DK_TERM_H__

#include <stdint.h>

namespace dk
{

enum class term_text_attrib : uint32_t
{
	DEFAULT = 0,
	BOLD,
	NOT_BOLD
};

enum class term_text_color : uint32_t
{
	DEFAULT = 0,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	GRAY,
	LIGHT_RED,
	LIGHT_GREEN,
	LIGHT_YELLOW,
	LIGHT_BLUE,
	LIGHT_MAGENTA,
	LIGHT_CYAN,
	LIGHT_WHITE,
	LIGHT_GRAY
};

enum class term_back_color : uint32_t
{
	DEFAULT = 0,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	GRAY,
	LIGHT_RED,
	LIGHT_GREEN,
	LIGHT_YELLOW,
	LIGHT_BLUE,
	LIGHT_MAGENTA,
	LIGHT_CYAN,
	LIGHT_WHITE,
	LIGHT_GRAY
};

class term
{
public:
	static void set(term_text_attrib attrib);
	static void set(term_text_color color);
	static void set(term_back_color color);
};

}

#endif  //  !__DK_TERM_H__
