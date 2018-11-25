#ifndef __DK_MATH_VEC4_H__
#define __DK_MATH_VEC4_H__

#include "math/vec3.h"

namespace dk
{

template<typename T>
class vec4
{
public:
	T x;
	T y;
	T z;
	T w;

	constexpr vec4() = default;
	template<typename A> constexpr vec4(const vec4<A>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
	template<typename A> constexpr vec4(const vec3<A>& other, A w_ = 0) : x(other.x), y(other.y), z(other.z), w(w_) {}
	template<typename A> constexpr vec4(A a) : x(a), y(a), z(a), w(a) {}
	template<typename A> constexpr vec4(A x_, A y_, A z_, A w_ = 0) : x(x_), y(y_), z(z_), w(w_) {}

	template<typename A> constexpr operator vec3<A>() const { return { (A)x, (A)y, (A)z }; }
	template<typename A> constexpr operator vec4<A>() const { return { (A)x, (A)y, (A)z, (A)w }; }

	template<typename A> constexpr vec4<decltype(A{} + T{})> operator+(A a) const { return { x + a, y + a, z + a, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} - T{})> operator-(A a) const { return { x - a, y - a, z - a, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} * T{})> operator*(A a) const { return { x * a, y * a, z * a, w * a }; }
	template<typename A> constexpr vec4<decltype(A{} / T{})> operator/(A a) const { return { x / a, y / a, z / a, w / a }; }

	template<typename A> constexpr vec4<decltype(A{} + T{})> operator+(const vec4<A>& other) const { return { x + other.x, y + other.y, z + other.z, 0 }; }
	template<typename A> constexpr vec4<decltype(A{} - T{})> operator-(const vec4<A>& other) const { return { x - other.x, y - other.y, z - other.z, 0 }; }

	template<typename A> constexpr vec4& operator+=(A a) { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr vec4& operator-=(A a) { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr vec4& operator*=(A a) { x *= a; y *= a; z *= a; w *= a; return *this; }
	template<typename A> constexpr vec4& operator/=(A a) { x /= a; y /= a; z /= a; w /= a; return *this; }

	template<typename A> constexpr vec4& operator+=(const vec4<A>& other) { x += other.x; y += other.y; z += other.z; w = 0; return *this; }
	template<typename A> constexpr vec4& operator-=(const vec4<A>& other) { x += other.x; y += other.y; z += other.z; w = 0; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const vec4<A>& other) const { return x * other.x + y * other.y + z * other.z; }
	template<typename A> constexpr vec4<decltype(A{} * T{})> cross(const vec4<A>& other) const { return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0 }; }

	template<typename A = T> constexpr A length() const { return maths::sqrt<A>(x * x + y * y + z * z); }

	constexpr vec4& normalize() { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() { return &x; }
	constexpr T* end()   { return &w + 1; }

	constexpr const T* begin() const { &x; }
	constexpr const T* end()   const { &w + 1; }

	constexpr T* data() const { return &x; }
};

}

#endif  //  !__DK_VEC4_H__
