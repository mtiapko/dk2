#ifndef __DK_MATH_SIMD_MAT4F_H__
#define __DK_MATH_SIMD_MAT4F_H__

#include "math/SIMD_Vec4f.h"

namespace dk::math
{

class SIMD_Mat4f
{
private:
	static __m128 mul_row_by_mat(const __m128& row, const SIMD_Mat4f& mat) noexcept;

public:
	union
	{
		float  data[4 * 4];
		__m128 row[4];
	};

	SIMD_Mat4f() = default;
	SIMD_Mat4f(const SIMD_Mat4f& that) noexcept;
	SIMD_Mat4f(float data_[]) noexcept;
	SIMD_Mat4f(__m128 row[]) noexcept;
	SIMD_Mat4f(__m128 row0, __m128 row1, __m128 row2, __m128 row3) noexcept;
	SIMD_Mat4f(float e) noexcept;
	SIMD_Mat4f(float e00, float e11, float e22, float e33 = 1.0f) noexcept;
	SIMD_Mat4f(float e00, float e10, float e20, float e30,
		float e01, float e11, float e21, float e31,
		float e02, float e12, float e22, float e32,
		float e03, float e13, float e23, float e33) noexcept;
	SIMD_Mat4f(SIMD_Vec4f vec) noexcept;
	SIMD_Mat4f(SIMD_Vec4f row0, SIMD_Vec4f row1, SIMD_Vec4f row2, SIMD_Vec4f row3) noexcept;

	static SIMD_Mat4f get_unit() noexcept;
	static SIMD_Mat4f get_orthographic(float left, float right, float bottom, float top, float near, float far) noexcept;
	static SIMD_Mat4f get_perspective(float fov, float ratio, float near, float far) noexcept;

	static SIMD_Mat4f get_translate(const SIMD_Vec4f& vec) noexcept;

	static SIMD_Mat4f get_rot_x(float angle) noexcept;
	static SIMD_Mat4f get_rot_y(float angle) noexcept;
	static SIMD_Mat4f get_rot_z(float angle) noexcept;
	static SIMD_Mat4f get_rot(const Vec3<float>& axis, float angle) noexcept;

	static SIMD_Mat4f get_look_at(const SIMD_Vec4f& pos, const SIMD_Vec4f& target, const SIMD_Vec4f& up) noexcept;

	SIMD_Mat4f operator+(float a) const noexcept;
	SIMD_Mat4f operator-(float a) const noexcept;
	SIMD_Mat4f operator*(float a) const noexcept;
	SIMD_Mat4f operator/(float a) const noexcept;

	SIMD_Vec4f operator*(const SIMD_Vec4f& vec) const noexcept;

	SIMD_Mat4f operator+(const SIMD_Mat4f& that) const noexcept;
	SIMD_Mat4f operator-(const SIMD_Mat4f& that) const noexcept;
	SIMD_Mat4f operator*(const SIMD_Mat4f& that) const noexcept;

	SIMD_Mat4f& operator+=(float a) noexcept;
	SIMD_Mat4f& operator-=(float a) noexcept;
	SIMD_Mat4f& operator*=(float a) noexcept;
	SIMD_Mat4f& operator/=(float a) noexcept;

	SIMD_Mat4f& operator+=(const SIMD_Mat4f& that) noexcept;
	SIMD_Mat4f& operator-=(const SIMD_Mat4f& that) noexcept;
	SIMD_Mat4f& operator*=(const SIMD_Mat4f& that) noexcept;

	SIMD_Mat4f& operator=(const SIMD_Mat4f& that) noexcept;

	SIMD_Mat4f& unit() noexcept;
	SIMD_Mat4f& orthographic(float left, float right, float bottom, float top, float near, float far) noexcept;
	SIMD_Mat4f& perspective(float fov, float ratio, float near, float far) noexcept;

	SIMD_Mat4f& translate(const SIMD_Vec4f& vec) noexcept;

	SIMD_Mat4f& rot_x(float angle) noexcept;
	SIMD_Mat4f& rot_y(float angle) noexcept;
	SIMD_Mat4f& rot_z(float angle) noexcept;
	SIMD_Mat4f& rot(const Vec3<float>& axis, float angle) noexcept;

	SIMD_Mat4f& look_at(const SIMD_Vec4f& pos, const SIMD_Vec4f& target, const SIMD_Vec4f& up) noexcept;
};

}

#endif  //  !__DK_MATH_SIMD_MAT4F_H__
