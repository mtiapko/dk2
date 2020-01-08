#ifndef __DK_OS_TERM_H__
#define __DK_OS_TERM_H__

#include <stdint.h>

namespace dk::os
{

enum class TermTextAttrib : uint32_t
{
	DEFAULT = 0,
	BOLD,
	NOT_BOLD
};

enum class TermTextColor : uint32_t
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

enum class TermBackColor : uint32_t
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

class Term
{
public:
	static void set(TermTextAttrib attrib) noexcept;
	static void set(TermTextColor color) noexcept;
	static void set(TermBackColor color) noexcept;
};

}

#endif // !__DK_OS_TERM_H__
