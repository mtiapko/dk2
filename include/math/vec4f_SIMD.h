#ifndef __DK_VEC4F_SIMD_H__
#define __DK_VEC4F_SIMD_H__

#include "math/SIMD.h"
#include "math/vec4.h"

namespace dk
{

class vec4f_SIMD
{
public:
	union
	{
		float  data[4];
		__m128 row;
	};

	vec4f_SIMD() = default;
	vec4f_SIMD(const vec4f_SIMD& other);
	vec4f_SIMD(float data_[]);
	vec4f_SIMD(__m128 row_[]);
	vec4f_SIMD(float a);
	vec4f_SIMD(float x, float y, float z, float w = 0);
	vec4f_SIMD(__m128 row_);
	template<typename T> vec4f_SIMD(const vec3<T>& other, T w = 0) { row = _mm_set_ps(other.x, other.y, other.z, w); }
	template<typename T> vec4f_SIMD(const vec4<T>& other) { row = _mm_set_ps(other.x, other.y, other.z, other.w); }


	template<typename T> operator vec3<T>() const { return { data[0], data[1], data[2] }; }
	template<typename T> operator vec4<T>() const { return { data[0], data[1], data[2], data[3] }; }

	vec4f_SIMD operator+(float a) const;
	vec4f_SIMD operator-(float a) const;
	vec4f_SIMD operator*(float a) const;
	vec4f_SIMD operator/(float a) const;

	vec4f_SIMD operator+(const vec4f_SIMD& other) const;
	vec4f_SIMD operator-(const vec4f_SIMD& other) const;

	vec4f_SIMD& operator+=(float a);
	vec4f_SIMD& operator-=(float a);
	vec4f_SIMD& operator*=(float a);
	vec4f_SIMD& operator/=(float a);

	vec4f_SIMD& operator+=(const vec4f_SIMD& other);
	vec4f_SIMD& operator-=(const vec4f_SIMD& other);

	float dot(const vec4f_SIMD& other) const;
	vec4f_SIMD cross(const vec4f_SIMD& other) const;

	float length() const;

	vec4f_SIMD& normalize();

	float* begin();
	float* end();

	const float* begin() const;
	const float* end()   const;
};

}

#endif  //  !__DK_VEC4F_SIMD_H__
