#ifndef __DK_MATH_FUNC_H__
#define __DK_MATH_FUNC_H__

#include <math.h>
#include <algorithm>

namespace dk::math
{

class Algo
{
public:
	static constexpr float PI = 3.1415926f;

	static constexpr float to_rad(float angle) noexcept { return (PI / 180.0f) * angle; }

	template<typename T> static constexpr T sqrt(T x) noexcept { return std::sqrt(x); }
	template<typename T> static constexpr T cos(T x) noexcept { return std::cos(x); }
	template<typename T> static constexpr T sin(T x) noexcept { return std::sin(x); }
	template<typename T> static constexpr T tan(T x) noexcept { return std::tan(x); }

	template<typename T>
	static constexpr T clamp(const T& v, const T& l, const T& h) noexcept { return std::clamp(v, l, h); }
};

}

#endif  //  !__DK_MATH_FUNC_H__
