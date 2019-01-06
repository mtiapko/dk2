#ifndef __DK_MATH_VEC4_H__
#define __DK_MATH_VEC4_H__

#include "math/vec3.h"

namespace dk::math
{

template<typename T>
class vec4
{
public:
	T x;
	T y;
	T z;
	T w;

	constexpr vec4() noexcept = default;
	template<typename A> constexpr vec4(const vec4<A>& that) noexcept : x(that.x), y(that.y), z(that.z), w(that.w) {}
	template<typename A> constexpr vec4(const vec3<A>& that, A w_ = 0) noexcept : x(that.x), y(that.y), z(that.z), w(w_) {}
	template<typename A> constexpr vec4(A a) noexcept : x(a), y(a), z(a), w(a) {}
	template<typename A> constexpr vec4(A x_, A y_, A z_, A w_ = 0) noexcept : x(x_), y(y_), z(z_), w(w_) {}

	template<typename A> constexpr operator vec3<A>() const noexcept { return { (A)x, (A)y, (A)z }; }
	template<typename A> constexpr operator vec4<A>() const noexcept { return { (A)x, (A)y, (A)z, (A)w }; }

	template<typename A> constexpr vec4<decltype(A{} + T{})> operator+(A a) const noexcept { return { x + a, y + a, z + a, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} - T{})> operator-(A a) const noexcept { return { x - a, y - a, z - a, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} * T{})> operator*(A a) const noexcept { return { x * a, y * a, z * a, w * a }; }
	template<typename A> constexpr vec4<decltype(A{} / T{})> operator/(A a) const noexcept { return { x / a, y / a, z / a, w / a }; }

	template<typename A> constexpr vec4<decltype(A{} + T{})> operator+(const vec4<A>& that) const noexcept { return { x + that.x, y + that.y, z + that.z, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} - T{})> operator-(const vec4<A>& that) const noexcept { return { x - that.x, y - that.y, z - that.z, 0 }; }

	template<typename A> constexpr vec4& operator+=(A a) noexcept { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr vec4& operator-=(A a) noexcept { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr vec4& operator*=(A a) noexcept { x *= a; y *= a; z *= a; w *= a; return *this; }
	template<typename A> constexpr vec4& operator/=(A a) noexcept { x /= a; y /= a; z /= a; w /= a; return *this; }

	template<typename A> constexpr vec4& operator+=(const vec4<A>& that) noexcept { x += that.x; y += that.y; z += that.z; w = 0; return *this; }
	template<typename A> constexpr vec4& operator-=(const vec4<A>& that) noexcept { x += that.x; y += that.y; z += that.z; w = 0; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const vec4<A>& that) const noexcept { return x * that.x + y * that.y + z * that.z; }
	template<typename A> constexpr vec4<decltype(A{} * T{})> cross(const vec4<A>& that) const noexcept { return { y * that.z - z * that.y, z * that.x - x * that.z, x * that.y - y * that.x, 0 }; }

	template<typename A = T> constexpr A length() const noexcept { return func::sqrt<A>(x * x + y * y + z * z); }

	constexpr vec4& normalize() noexcept { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() noexcept { return &x; }
	constexpr T* end()   noexcept { return &w + 1; }

	constexpr const T* begin() const noexcept { &x; }
	constexpr const T* end()   const noexcept { &w + 1; }

	constexpr T* data() const noexcept { return &x; }
};

}

#endif  //  !__DK_MATH_VEC4_H__
