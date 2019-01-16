#ifndef __DK_MATH_VEC4F_SIMD_H__
#define __DK_MATH_VEC4F_SIMD_H__

#include "util/SIMD.h"
#include "math/Vec4.h"

namespace dk::math
{

class SIMD_Vec4f
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		__m128 row;
	};

	SIMD_Vec4f() noexcept = default;
	SIMD_Vec4f(const SIMD_Vec4f& that) noexcept;
	SIMD_Vec4f(float data_[]) noexcept;
	SIMD_Vec4f(__m128 row_[]) noexcept;
	SIMD_Vec4f(float a) noexcept;
	SIMD_Vec4f(float x, float y, float z, float w = 0) noexcept;
	SIMD_Vec4f(__m128 row_) noexcept;
	template<typename T> SIMD_Vec4f(const Vec3<T>& that, T w = 0) noexcept { row = _mm_set_ps(that.x, that.y, that.z, w); }
	template<typename T> SIMD_Vec4f(const Vec4<T>& that) noexcept { row = _mm_set_ps(that.x, that.y, that.z, that.w); }


	template<typename T> operator Vec3<T>() const noexcept { return { x, y, z }; }
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
};

}

#endif  //  !__DK_MATH_VEC4F_SIMD_H__
