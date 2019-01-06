#ifndef __DK_MATH_VEC3_H__
#define __DK_MATH_VEC3_H__

#include "math/func.h"

namespace dk::math
{

template<typename T>
class vec3
{
public:
	T x;
	T y;
	T z;

	constexpr vec3() noexcept = default;
	template<typename A> constexpr vec3(const vec3<A>& that) noexcept : x(that.x), y(that.y), z(that.z) {}
	template<typename A> constexpr vec3(A a) noexcept : x(a), y(a), z(a) {}
	template<typename A> constexpr vec3(A x_, A y_, A z_) noexcept : x(x_), y(y_), z(z_) {}

	template<typename A> constexpr operator vec3<A>() const noexcept { return { (A)x, (A)y, (A)z }; }

	template<typename A> constexpr vec3<decltype(A{} + T{})> operator+(A a) const noexcept { return { x + a, y + a, z + a }; }
	template<typename A> constexpr vec3<decltype(A{} - T{})> operator-(A a) const noexcept { return { x - a, y - a, z - a }; }
	template<typename A> constexpr vec3<decltype(A{} * T{})> operator*(A a) const noexcept { return { x * a, y * a, z * a }; }
	template<typename A> constexpr vec3<decltype(A{} / T{})> operator/(A a) const noexcept { return { x / a, y / a, z / a }; }

	template<typename A> constexpr vec3<decltype(A{} + T{})> operator+(const vec3<A>& that) const noexcept { return { x + that.x, y + that.y, z + that.z }; }
	template<typename A> constexpr vec3<decltype(A{} - T{})> operator-(const vec3<A>& that) const noexcept { return { x - that.x, y - that.y, z - that.z }; }

	template<typename A> constexpr vec3& operator+=(A a) noexcept { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr vec3& operator-=(A a) noexcept { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr vec3& operator*=(A a) noexcept { x *= a; y *= a; z *= a; return *this; }
	template<typename A> constexpr vec3& operator/=(A a) noexcept { x /= a; y /= a; z /= a; return *this; }

	template<typename A> constexpr vec3& operator+=(const vec3<A>& that) noexcept { x += that.x; y += that.y; z += that.z; return *this; }
	template<typename A> constexpr vec3& operator-=(const vec3<A>& that) noexcept { x += that.x; y += that.y; z += that.z; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const vec3<A>& that) const noexcept { return x * that.x + y * that.y + z * that.z; }
	template<typename A> constexpr vec3<decltype(A{} * T{})> cross(const vec3<A>& that) const noexcept { return { y * that.z - z * that.y, z * that.x - x * that.z, x * that.y - y * that.x }; }

	template<typename A = T> constexpr A length() const noexcept { return func::sqrt<A>(x * x + y * y + z * z); }

	constexpr vec3& normalize() noexcept { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() noexcept { return &x; }
	constexpr T* end()   noexcept { return &z + 1; }

	constexpr const T* begin() const noexcept { return &x; }
	constexpr const T* end()   const noexcept { return &z + 1; }

	constexpr T* data() noexcept { return &x; }
};

}

#endif  //  !__DK_MATH_VEC3_H__
