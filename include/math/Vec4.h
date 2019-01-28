#ifndef __DK_MATH_VEC4_H__
#define __DK_MATH_VEC4_H__

#include "math/Vec3.h"

namespace dk::math
{

template<typename T>
class Vec4
{
public:
	T x;
	T y;
	T z;
	T w;

	constexpr Vec4() noexcept = default;
	template<typename A> constexpr Vec4(const Vec4<A>& that) noexcept : x(that.x), y(that.y), z(that.z), w(that.w) {}
	template<typename A> constexpr Vec4(const Vec3<A>& that, A w_ = 0) noexcept : x(that.x), y(that.y), z(that.z), w(w_) {}
	template<typename A> constexpr Vec4(A a) noexcept : x(a), y(a), z(a), w(a) {}
	template<typename A> constexpr Vec4(A x_, A y_, A z_, A w_ = 0) noexcept : x(x_), y(y_), z(z_), w(w_) {}

	template<typename A> constexpr operator Vec3<A>() const noexcept { return { (A)x, (A)y, (A)z }; }
	template<typename A> constexpr operator Vec4<A>() const noexcept { return { (A)x, (A)y, (A)z, (A)w }; }

	template<typename A> constexpr Vec4<decltype(A{} + T{})> operator+(A a) const noexcept { return { x + a, y + a, z + a, 0 }; }
	template<typename A> constexpr Vec4<decltype(A{} - T{})> operator-(A a) const noexcept { return { x - a, y - a, z - a, 0 }; }
	template<typename A> constexpr Vec4<decltype(A{} * T{})> operator*(A a) const noexcept { return { x * a, y * a, z * a, w * a }; }
	template<typename A> constexpr Vec4<decltype(A{} / T{})> operator/(A a) const noexcept { return { x / a, y / a, z / a, w / a }; }

	template<typename A> constexpr Vec4<decltype(A{} + T{})> operator+(const Vec4<A>& that) const noexcept { return { x + that.x, y + that.y, z + that.z, 0 }; }
	template<typename A> constexpr Vec4<decltype(A{} - T{})> operator-(const Vec4<A>& that) const noexcept { return { x - that.x, y - that.y, z - that.z, 0 }; }

	template<typename A> constexpr Vec4& operator+=(A a) noexcept { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr Vec4& operator-=(A a) noexcept { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr Vec4& operator*=(A a) noexcept { x *= a; y *= a; z *= a; w *= a; return *this; }
	template<typename A> constexpr Vec4& operator/=(A a) noexcept { x /= a; y /= a; z /= a; w /= a; return *this; }

	template<typename A> constexpr Vec4& operator+=(const Vec4<A>& that) noexcept { x += that.x; y += that.y; z += that.z; w = 0; return *this; }
	template<typename A> constexpr Vec4& operator-=(const Vec4<A>& that) noexcept { x -= that.x; y -= that.y; z -= that.z; w = 0; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const Vec4<A>& that) const noexcept { return x * that.x + y * that.y + z * that.z; }
	template<typename A> constexpr Vec4<decltype(A{} * T{})> cross(const Vec4<A>& that) const noexcept { return { y * that.z - z * that.y, z * that.x - x * that.z, x * that.y - y * that.x, 0 }; }

	template<typename A = T> constexpr A length() const noexcept { return Algo::sqrt<A>(x * x + y * y + z * z); }

	constexpr Vec4& normalize() noexcept { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() noexcept { return &x; }
	constexpr T* end()   noexcept { return &w + 1; }

	constexpr const T* begin() const noexcept { &x; }
	constexpr const T* end()   const noexcept { &w + 1; }

	constexpr T* data() const noexcept { return &x; }
};

}

#endif  //  !__DK_MATH_VEC4_H__
