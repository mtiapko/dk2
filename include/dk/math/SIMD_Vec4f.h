#ifndef __DK_MATH_VEC4F_SIMD_H__
#define __DK_MATH_VEC4F_SIMD_H__

#include "dk/util/SIMD.h"
#include "dk/math/Vec4.h"

namespace dk::math
{

class SIMD_Vec4f
{
public:
	union
	{
		// TODO: static_assert for endian
		struct
		{
			union { float x; float r; };
			union { float y; float g; };
			union { float z; float b; };
			union { float w; float a; };
		};

		__m128 row;
	};

	SIMD_Vec4f() noexcept = default;
	SIMD_Vec4f(const SIMD_Vec4f& that) noexcept = default;
	SIMD_Vec4f(float data_[]) noexcept;
	SIMD_Vec4f(__m128 row_[]) noexcept;
	SIMD_Vec4f(float a) noexcept;
	SIMD_Vec4f(float x, float y, float z, float w = 0) noexcept;
	SIMD_Vec4f(__m128 row_) noexcept;
	template<typename T> SIMD_Vec4f(const Vec3<T>& that, T w = 0) noexcept { row = _mm_set_ps(w, that.z, that.y, that.x); }
	template<typename T> SIMD_Vec4f(const Vec4<T>& that) noexcept { row = _mm_set_ps(that.w, that.z, that.y, that.x); }


	template<typename T> operator Vec3<T>() const noexcept { return Vec3<T> { x, y, z }; }
	template<typename T> operator Vec4<T>() const noexcept { return { x, y, z, w }; }

	SIMD_Vec4f operator+(float a) const noexcept;
	SIMD_Vec4f operator-(float a) const noexcept;
	SIMD_Vec4f operator*(float a) const noexcept;
	SIMD_Vec4f operator/(float a) const noexcept;

	SIMD_Vec4f operator+(const SIMD_Vec4f& that) const noexcept;
	SIMD_Vec4f operator-(const SIMD_Vec4f& that) const noexcept;

	SIMD_Vec4f& operator+=(float a) noexcept;
	SIMD_Vec4f& operator-=(float a) noexcept;
	SIMD_Vec4f& operator*=(float a) noexcept;
	SIMD_Vec4f& operator/=(float a) noexcept;

	SIMD_Vec4f& operator+=(const SIMD_Vec4f& that) noexcept;
	SIMD_Vec4f& operator-=(const SIMD_Vec4f& that) noexcept;

	float dot(const SIMD_Vec4f& that) const noexcept;
	SIMD_Vec4f cross(const SIMD_Vec4f& that) const noexcept;

	float length() const noexcept;

	SIMD_Vec4f& normalize() noexcept;

	float* begin() noexcept;
	float* end() noexcept;

	const float* begin() const noexcept;
	const float* end()   const noexcept;

	float* data() noexcept { return &x; }

	//  TODO: remove
	friend std::ostream& operator<<(std::ostream& out, const SIMD_Vec4f& vec)
	{
		out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';
		return out;
	}
};

}

#endif  //  !__DK_MATH_VEC4F_SIMD_H__
