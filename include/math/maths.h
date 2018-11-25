#ifndef __DK_MATHS_H__
#define __DK_MATHS_H__

#include <cmath>

namespace dk
{

class maths
{
public:
	static constexpr float PI = 3.1415926f;

	static constexpr float to_rad(float angle) { return (maths::PI / 180.0f) * angle; }

	template<typename T> static T sqrt(T x) { return std::sqrt(x); }
	template<typename T> static T cos(T x) { return std::cos(x); }
	template<typename T> static T sin(T x) { return std::sin(x); }
	template<typename T> static T tan(T x) { return std::tan(x); }
};

}

#endif  //  !__DK_MATHS_H__
