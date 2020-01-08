#ifndef __DK_MATH_VEC3_H__
#define __DK_MATH_VEC3_H__

#include <iostream>  //  TODO: remove

#include "dk/math/Algo.h"

namespace dk::math
{

template<typename T>
class Vec3
{
public:
	union { T x; T r; };
	union { T y; T g; };
	union { T z; T b; };

	constexpr Vec3() noexcept = default;
	template<typename A> constexpr Vec3(const Vec3<A>& that) noexcept : x(that.x), y(that.y), z(that.z) {}
	template<typename A> constexpr Vec3(A a) noexcept : x(a), y(a), z(a) {}
	template<typename A> constexpr Vec3(A x_, A y_, A z_) noexcept : x(x_), y(y_), z(z_) {}

	template<typename A> constexpr operator Vec3<A>() const noexcept { return { (A)x, (A)y, (A)z }; }

	template<typename A> constexpr Vec3<decltype(A{} + T{})> operator+(A a) const noexcept { return { x + a, y + a, z + a }; }
	template<typename A> constexpr Vec3<decltype(A{} - T{})> operator-(A a) const noexcept { return { x - a, y - a, z - a }; }
	template<typename A> constexpr Vec3<decltype(A{} * T{})> operator*(A a) const noexcept { return { x * a, y * a, z * a }; }
	template<typename A> constexpr Vec3<decltype(A{} / T{})> operator/(A a) const noexcept { return { x / a, y / a, z / a }; }

	template<typename A> constexpr Vec3<decltype(A{} + T{})> operator+(const Vec3<A>& that) const noexcept { return { x + that.x, y + that.y, z + that.z }; }
	template<typename A> constexpr Vec3<decltype(A{} - T{})> operator-(const Vec3<A>& that) const noexcept { return { x - that.x, y - that.y, z - that.z }; }

	template<typename A> constexpr Vec3& operator+=(A a) noexcept { x += a; y += a; z += a; return *this; }
	template<typename A> constexpr Vec3& operator-=(A a) noexcept { x -= a; y -= a; z -= a; return *this; }
	template<typename A> constexpr Vec3& operator*=(A a) noexcept { x *= a; y *= a; z *= a; return *this; }
	template<typename A> constexpr Vec3& operator/=(A a) noexcept { x /= a; y /= a; z /= a; return *this; }

	template<typename A> constexpr Vec3& operator+=(const Vec3<A>& that) noexcept { x += that.x; y += that.y; z += that.z; return *this; }
	template<typename A> constexpr Vec3& operator-=(const Vec3<A>& that) noexcept { x -= that.x; y -= that.y; z -= that.z; return *this; }

	template<typename A> constexpr decltype(A{} * T{}) dot(const Vec3<A>& that) const noexcept { return x * that.x + y * that.y + z * that.z; }
	template<typename A> constexpr Vec3<decltype(A{} * T{})> cross(const Vec3<A>& that) const noexcept { return { y * that.z - z * that.y, z * that.x - x * that.z, x * that.y - y * that.x }; }

	template<typename A = T> constexpr A length() const noexcept { return Algo::sqrt<A>(x * x + y * y + z * z); }

	constexpr Vec3& normalize() noexcept { const float rlen = 1 / this->length(); x *= rlen; y *= rlen; z *= rlen; return *this; }

	constexpr T* begin() noexcept { return &x; }
	constexpr T* end()   noexcept { return &z + 1; }

	constexpr const T* begin() const noexcept { return &x; }
	constexpr const T* end()   const noexcept { return &z + 1; }

	constexpr T* data() noexcept { return &x; }

	//  TODO: remove
	friend std::ostream& operator<<(std::ostream& out, const Vec3<T>& vec)
	{
		out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
		return out;
	}
};

}

#endif  //  !__DK_MATH_VEC3_H__
