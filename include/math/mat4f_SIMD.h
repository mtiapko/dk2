#ifndef __DK_MATH_MAT4F_SIMD_H__
#define __DK_MATH_MAT4F_SIMD_H__

#include "math/vec4f_SIMD.h"

namespace dk::math
{

class mat4f_SIMD
{
private:
	static __m128 mul_row_by_mat(const __m128& row, const mat4f_SIMD& mat) noexcept;

public:
	union
	{
		float  data[4 * 4];
		__m128 row[4];
	};

	mat4f_SIMD() = default;
	mat4f_SIMD(const mat4f_SIMD& that) noexcept;
	mat4f_SIMD(float data_[]) noexcept;
	mat4f_SIMD(__m128 row[]) noexcept;
	mat4f_SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3) noexcept;
	mat4f_SIMD(float e) noexcept;
	mat4f_SIMD(float e00, float e11, float e22, float e33 = 1.0f) noexcept;
	mat4f_SIMD(float e00, float e10, float e20, float e30,
		float e01, float e11, float e21, float e31,
		float e02, float e12, float e22, float e32,
		float e03, float e13, float e23, float e33) noexcept;
	mat4f_SIMD(vec4f_SIMD vec) noexcept;
	mat4f_SIMD(vec4f_SIMD row0, vec4f_SIMD row1, vec4f_SIMD row2, vec4f_SIMD row3) noexcept;

	static mat4f_SIMD get_unit() noexcept;
	static mat4f_SIMD get_orthographic(float left, float right, float bottom, float top, float near, float far) noexcept;
	static mat4f_SIMD get_perspective(float fov, float ratio, float near, float far) noexcept;

	static mat4f_SIMD get_translate(const vec4f_SIMD& vec) noexcept;

	static mat4f_SIMD get_rot_x(float angle) noexcept;
	static mat4f_SIMD get_rot_y(float angle) noexcept;
	static mat4f_SIMD get_rot_z(float angle) noexcept;
	static mat4f_SIMD get_rot(const vec3<float>& axis, float angle) noexcept;

	static mat4f_SIMD get_look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up) noexcept;

	mat4f_SIMD operator+(float a) const noexcept;
	mat4f_SIMD operator-(float a) const noexcept;
	mat4f_SIMD operator*(float a) const noexcept;
	mat4f_SIMD operator/(float a) const noexcept;

	vec4f_SIMD operator*(const vec4f_SIMD& vec) const noexcept;

	mat4f_SIMD operator+(const mat4f_SIMD& that) const noexcept;
	mat4f_SIMD operator-(const mat4f_SIMD& that) const noexcept;
	mat4f_SIMD operator*(const mat4f_SIMD& that) const noexcept;

	mat4f_SIMD& operator+=(float a) noexcept;
	mat4f_SIMD& operator-=(float a) noexcept;
	mat4f_SIMD& operator*=(float a) noexcept;
	mat4f_SIMD& operator/=(float a) noexcept;

	mat4f_SIMD& operator+=(const mat4f_SIMD& that) noexcept;
	mat4f_SIMD& operator-=(const mat4f_SIMD& that) noexcept;
	mat4f_SIMD& operator*=(const mat4f_SIMD& that) noexcept;

	mat4f_SIMD& operator=(const mat4f_SIMD& that) noexcept;

	mat4f_SIMD& unit() noexcept;
	mat4f_SIMD& orthographic(float left, float right, float bottom, float top, float near, float far) noexcept;
	mat4f_SIMD& perspective(float fov, float ratio, float near, float far) noexcept;

	mat4f_SIMD& translate(const vec4f_SIMD& vec) noexcept;

	mat4f_SIMD& rot_x(float angle) noexcept;
	mat4f_SIMD& rot_y(float angle) noexcept;
	mat4f_SIMD& rot_z(float angle) noexcept;
	mat4f_SIMD& rot(const vec3<float>& axis, float angle) noexcept;

	mat4f_SIMD& look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up) noexcept;
};

}

#endif  //  !__DK_MATH_MAT4F_SIMD_H__
