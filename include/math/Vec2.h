#ifndef __DK_MATH_VEC2_H__
#define __DK_MATH_VEC2_H__

#include <iostream>  //  TODO: remove

#include "math/Algo.h"

namespace dk::math
{

template<typename T>
class Vec2
{
public:
	T x;
	T y;

	constexpr Vec2() noexcept = default;
	template<typename A> constexpr Vec2(const Vec2<A>& that) noexcept : x(that.x), y(that.y) {}
	template<typename A> constexpr Vec2(A a) noexcept : x(a), y(a) {}
	template<typename A> constexpr Vec2(A x_, A y_) noexcept : x(x_), y(y_) {}

	template<typename A> constexpr operator Vec2<A>() const noexcept { return { (A)x, (A)y }; }

	template<typename A> constexpr Vec2<decltype(A{} + T{})> operator+(A a) const noexcept { return { x + a, y + a }; }
	template<typename A> constexpr Vec2<decltype(A{} - T{})> operator-(A a) const noexcept { return { x - a, y - a }; }
	template<typename A> constexpr Vec2<decltype(A{} * T{})> operator*(A a) const noexcept { return { x * a, y * a }; }
	template<typename A> constexpr Vec2<decltype(A{} / T{})> operator/(A a) const noexcept { return { x / a, y / a }; }

	template<typename A> constexpr Vec2<decltype(A{} + T{})> operator+(const Vec2<A>& that) const noexcept { return { x + that.x, y + that.y }; }
	template<typename A> constexpr Vec2<decltype(A{} - T{})> operator-(const Vec2<A>& that) const noexcept { return { x - that.x, y - that.y }; }

	template<typename A> constexpr Vec2& operator+=(A a) noexcept { x += a; y += a; return *this; }
	template<typename A> constexpr Vec2& operator-=(A a) noexcept { x -= a; y -= a; return *this; }
	template<typename A> constexpr Vec2& operator*=(A a) noexcept { x *= a; y *= a; return *this; }
	template<typename A> constexpr Vec2& operator/=(A a) noexcept { x /= a; y /= a; return *this; }

	template<typename A> constexpr Vec2& operator+=(const Vec2<A>& that) noexcept { x += that.x; y += that.y; return *this; }
	template<typename A> constexpr Vec2& operator-=(const Vec2<A>& that) noexcept { x -= that.x; y -= that.y; return *this; }

	template<typename A = T> constexpr A length() const noexcept { return Algo::sqrt<A>(x * x + y * y); }

	constexpr Vec2& normalize() noexcept { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; return *this; }

	constexpr T* begin() noexcept { return &x; }
	constexpr T* end()   noexcept { return &y + 1; }

	constexpr const T* begin() const noexcept { return &x; }
	constexpr const T* end()   const noexcept { return &y + 1; }

	constexpr T* data() noexcept { return &x; }

	//  TODO: remove
	friend std::ostream& operator<<(std::ostream& out, const Vec2<T>& vec)
	{
		out << '(' << vec.x << ", " << vec.y << ')';
		return out;
	}
};

}

#endif  //  !__DK_MATH_VEC2_H__
