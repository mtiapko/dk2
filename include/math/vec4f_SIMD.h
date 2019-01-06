#ifndef __DK_MATH_VEC4F_SIMD_H__
#define __DK_MATH_VEC4F_SIMD_H__

#include "util/SIMD.h"
#include "math/vec4.h"

namespace dk::math
{

class vec4f_SIMD
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

	vec4f_SIMD() noexcept = default;
	vec4f_SIMD(const vec4f_SIMD& that) noexcept;
	vec4f_SIMD(float data_[]) noexcept;
	vec4f_SIMD(__m128 row_[]) noexcept;
	vec4f_SIMD(float a) noexcept;
	vec4f_SIMD(float x, float y, float z, float w = 0) noexcept;
	vec4f_SIMD(__m128 row_) noexcept;
	template<typename T> vec4f_SIMD(const vec3<T>& that, T w = 0) noexcept { row = _mm_set_ps(that.x, that.y, that.z, w); }
	template<typename T> vec4f_SIMD(const vec4<T>& that) noexcept { row = _mm_set_ps(that.x, that.y, that.z, that.w); }


	template<typename T> operator vec3<T>() const noexcept { return { x, y, z }; }
	template<typename T> operator vec4<T>() const noexcept { return { x, y, z, w }; }

	vec4f_SIMD operator+(float a) const noexcept;
	vec4f_SIMD operator-(float a) const noexcept;
	vec4f_SIMD operator*(float a) const noexcept;
	vec4f_SIMD operator/(float a) const noexcept;

	vec4f_SIMD operator+(const vec4f_SIMD& that) const noexcept;
	vec4f_SIMD operator-(const vec4f_SIMD& that) const noexcept;

	vec4f_SIMD& operator+=(float a) noexcept;
	vec4f_SIMD& operator-=(float a) noexcept;
	vec4f_SIMD& operator*=(float a) noexcept;
	vec4f_SIMD& operator/=(float a) noexcept;

	vec4f_SIMD& operator+=(const vec4f_SIMD& that) noexcept;
	vec4f_SIMD& operator-=(const vec4f_SIMD& that) noexcept;

	float dot(const vec4f_SIMD& that) const noexcept;
	vec4f_SIMD cross(const vec4f_SIMD& that) const noexcept;

	float length() const noexcept;

	vec4f_SIMD& normalize() noexcept;

	float* begin() noexcept;
	float* end() noexcept;

	const float* begin() const noexcept;
	const float* end()   const noexcept;
};

}

#endif  //  !__DK_MATH_VEC4F_SIMD_H__
