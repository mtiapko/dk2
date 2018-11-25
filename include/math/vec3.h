#ifndef __DK_VEC3_H__
#define __DK_VEC3_H__

#include "math/maths.h"

namespace dk
{

template<typename T>
class vec3
{
public:
	T x;
	T y;
	T z;

	constexpr vec3() = default;
	template<typename A> constexpr vec3(const vec3<A>& other) : x(other.x), y(other.y), z(other.z) {}
	template<typename A> constexpr vec3(A a) : x(a), y(a), z(a) {}
	template<typename A> constexpr vec3(A x_, A y_, A z_) : x(x_), y(y_), z(z_) {}

	template<typename A> constexpr operator vec3<A>() const { return { (A)x, (A)y, (A)z }; }

	template<typename A> constexpr vec3<decltype(A{} + T{})> operator+(A a) const { return { x + a, y + a, z + a }; }
	template<typename A> constexpr vec3<decltype(A{} - T{})> operator-(A a) const { return { x - a, y - a, z - a }; }
	template<typename A> constexpr vec3<decltype(A{} * T{})> operator*(A a) const { return { x * a, y * a, z * a }; }
	template<typename A> constexpr vec3<decltype(A{} / T{})> operator/(A a) const { return { x / a, y / a, z / a }; }

	template<typename A> constexpr vec3<decltype(A{} + T{})> operator+(const vec3<A>& other) const { return { x + other.x, y + other.y, z + other.z }; }
	template<typename A> constexpr vec3<decltype(A{} - T{})> operator-(const vec3<A>& other) const { return { x - other.x, y - other.y, z - other.z }; }

	template<typename A> constexpr vec3& operator+=(A a) { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr vec3& operator-=(A a) { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr vec3& operator*=(A a) { x *= a; y *= a; z *= a; return *this; }
	template<typename A> constexpr vec3& operator/=(A a) { x /= a; y /= a; z /= a; return *this; }

	template<typename A> constexpr vec3& operator+=(const vec3<A>& other) { x += other.x; y += other.y; z += other.z; return *this; }
	template<typename A> constexpr vec3& operator-=(const vec3<A>& other) { x += other.x; y += other.y; z += other.z; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const vec3<A>& other) const { return x * other.x + y * other.y + z * other.z; }
	template<typename A> constexpr vec3<decltype(A{} * T{})> cross(const vec3<A>& other) const { return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

	template<typename A = T> constexpr A length() const { return maths::sqrt<A>(x * x + y * y + z * z); }

	constexpr vec3& normalize() { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() { return &x; }
	constexpr T* end()   { return &z + 1; }

	constexpr const T* begin() const { return &x; }
	constexpr const T* end()   const { return &z + 1; }

	constexpr T* data() { return &x; }
};

}

#endif  //  !__DK_VEC3_H__
