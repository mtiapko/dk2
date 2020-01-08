#include <string.h>
#include "dk/math/SIMD_Mat4f.h"

namespace dk::math
{

SIMD_Mat4f::SIMD_Mat4f(float data_[]) noexcept
{
	row[0] = _mm_loadu_ps(data_);
	row[1] = _mm_loadu_ps(data_ + 4);
	row[2] = _mm_loadu_ps(data_ + 8);
	row[3] = _mm_loadu_ps(data_ + 12);
}

SIMD_Mat4f::SIMD_Mat4f(__m128 row_[]) noexcept
{
	row[0] = _mm_load_ps((float*)row_);
	row[1] = _mm_load_ps((float*)(row_ + 1));
	row[2] = _mm_load_ps((float*)(row_ + 2));
	row[3] = _mm_load_ps((float*)(row_ + 3));
}

SIMD_Mat4f::SIMD_Mat4f(__m128 row0, __m128 row1, __m128 row2, __m128 row3) noexcept
{
	row[0] = row0;
	row[1] = row1;
	row[2] = row2;
	row[3] = row3;
}

SIMD_Mat4f::SIMD_Mat4f(float e) noexcept
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, e);
	row[1] = _mm_set_ps(0.0f, 0.0f, e,    0.0f);
	row[2] = _mm_set_ps(0.0f, e,    0.0f, 0.0f);
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
}

SIMD_Mat4f::SIMD_Mat4f(float e00, float e11, float e22, float e33 /* = 1.0f */) noexcept
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, e00);
	row[1] = _mm_set_ps(0.0f, 0.0f, e11,  0.0f);
	row[2] = _mm_set_ps(0.0f, e22,  0.0f, 0.0f);
	row[3] = _mm_set_ps(e33,  0.0f, 0.0f, 0.0f);
}

SIMD_Mat4f::SIMD_Mat4f(float e00, float e10, float e20, float e30,
	float e01, float e11, float e21, float e31,
	float e02, float e12, float e22, float e32,
	float e03, float e13, float e23, float e33) noexcept
{
	row[0] = _mm_set_ps(e30, e20, e10, e00);
	row[1] = _mm_set_ps(e31, e21, e11, e01);
	row[2] = _mm_set_ps(e32, e22, e12, e02);
	row[3] = _mm_set_ps(e33, e23, e13, e03);
}

SIMD_Mat4f::SIMD_Mat4f(SIMD_Vec4f vec) noexcept
{
	row[0] = _mm_set_ps(0.0f,  0.0f,  0.0f,  vec.x);
	row[1] = _mm_set_ps(0.0f,  0.0f,  vec.y, 0.0f);
	row[2] = _mm_set_ps(0.0f,  vec.z, 0.0f,  0.0f);
	row[3] = _mm_set_ps(vec.w, 0.0f,  0.0f,  0.0f);
}

SIMD_Mat4f::SIMD_Mat4f(SIMD_Vec4f row0, SIMD_Vec4f row1, SIMD_Vec4f row2, SIMD_Vec4f row3) noexcept
{
	row[0] = row0.row;
	row[1] = row1.row;
	row[2] = row2.row;
	row[3] = row3.row;
}

/* static */ __m128 SIMD_Mat4f::mul_row_by_mat(const __m128& row, const SIMD_Mat4f& mat) noexcept
{
	__m128 res = _mm_mul_ps(_mm_shuffle_ps(row, row, 0), mat.row[0]);
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (1u << 6) | (1u << 4) | (1u << 2u) | 1u), mat.row[1]));
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (2u << 6) | (2u << 4) | (2u << 2u) | 2u), mat.row[2]));
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (3u << 6) | (3u << 4) | (3u << 2u) | 3u), mat.row[3]));

	return res;
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_unit() noexcept
{
	return {
		_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f),
		_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
		_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_orthographic(float left, float right, float bottom, float top, float near, float far) noexcept
{
	const float w = right - left;
	const float h = top - bottom;
	const float d = far - near;

	return {
		_mm_set_ps(-(right + left) / w, 0.0f,  0.0f,  2 / w),
		_mm_set_ps(-(top + bottom) / h, 0.0f,  2 / h, 0.0f),
		_mm_set_ps(-(near + far) / d,   -2 / d, 0.0f,  0.0f),
		_mm_set_ps(1.0f,                0.0f,  0.0f,  0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_perspective(float fov, float ratio, float near, float far) noexcept
{
	const float tf = Algo::tan(Algo::to_rad(fov / 2.0f));
	const float rd = near - far;

	return {
		_mm_set_ps(0.0f,                   0.0f,              0.0f,      1.0f / (ratio * tf)),
		_mm_set_ps(0.0f,                   0.0f,              1.0f / tf, 0.0f),
		_mm_set_ps(2.0f * far * near / rd, (far + near) / rd, 0.0f,      0.0f),
		_mm_set_ps(0.0f,                   -1.0f,             0.0f,      0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_translate(const SIMD_Vec4f& vec) noexcept
{
	return {
		_mm_set_ps(vec.x, 0.0f, 0.0f, 1.0f),
		_mm_set_ps(vec.y, 0.0f, 1.0f, 0.0f),
		_mm_set_ps(vec.z, 1.0f, 0.0f, 0.0f),
		_mm_set_ps(1.0f,  0.0f, 0.0f, 0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_rot_x(float angle) noexcept
{
	const float sinv = Algo::sin(Algo::to_rad(angle));
	const float cosv = Algo::cos(Algo::to_rad(angle));

	return {
		_mm_set_ps(0.0f, 0.0f,  0.0f, 1.0f),
		_mm_set_ps(0.0f, -sinv, cosv, 0.0f),
		_mm_set_ps(0.0f, cosv,  sinv, 0.0f),
		_mm_set_ps(1.0f, 0.0f,  0.0f, 0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_rot_y(float angle) noexcept
{
	const float sinv = Algo::sin(Algo::to_rad(angle));
	const float cosv = Algo::cos(Algo::to_rad(angle));

	return {
		_mm_set_ps(0.0f, sinv, 0.0f, cosv),
		_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
		_mm_set_ps(0.0f, cosv, 0.0f, -sinv),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_rot_z(float angle) noexcept
{
	const float sinv = Algo::sin(Algo::to_rad(angle));
	const float cosv = Algo::cos(Algo::to_rad(angle));

	return {
		_mm_set_ps(0.0f, 0.0f, -sinv, cosv),
		_mm_set_ps(0.0f, 0.0f, cosv,  sinv),
		_mm_set_ps(0.0f, 1.0f, 0.0f,  0.0f),
		_mm_set_ps(1.0f, 0.0f, 0.0f,  0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_rot(const Vec3<float>& axis, float angle) noexcept
{
	union
	{
		float x;
		float y;
		float z;
		float w;
		__m128 simd;
	} tmp;

	const float sinv = Algo::sin(Algo::to_rad(angle));
	const float cosv = Algo::cos(Algo::to_rad(angle));
	__m128 axisv = _mm_set_ps(0.0f, axis.z, axis.y, axis.x);
	__m128 rcosv = _mm_set1_ps(1.0f - cosv);
	__m128 t = _mm_mul_ps(axisv, rcosv);

	//  0: x * sin
	//  1: y * sin
	//  2: z * sin
	tmp.simd = _mm_mul_ps(axisv, _mm_set1_ps(sinv));

	return {
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.x)), _mm_set_ps(0.0f, tmp.y,  -tmp.z, cosv)),
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.y)), _mm_set_ps(0.0f, -tmp.x, cosv,   tmp.z)),
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.z)), _mm_set_ps(0.0f, cosv,   tmp.x,  -tmp.y)),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

/* static */ SIMD_Mat4f SIMD_Mat4f::get_look_at(const SIMD_Vec4f& pos, const SIMD_Vec4f& target, const SIMD_Vec4f& up) noexcept
{
	const SIMD_Vec4f camDir = (pos - target).normalize();
	const SIMD_Vec4f camRight = up.cross(camDir).normalize();
	const SIMD_Vec4f camUp = camDir.cross(camRight);

	return SIMD_Mat4f {
		_mm_set_ps(0.0f, camRight.z, camRight.y, camRight.x),
		_mm_set_ps(0.0f, camUp.z, camUp.y, camUp.x),
		_mm_set_ps(0.0f, camDir.z, camDir.y, camDir.x),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	} * get_translate(pos);
}

SIMD_Mat4f SIMD_Mat4f::operator+(float a) const noexcept
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_add_ps(row[0], t), _mm_add_ps(row[1], t), _mm_add_ps(row[2], t), _mm_add_ps(row[3], t) };
}

SIMD_Mat4f SIMD_Mat4f::operator-(float a) const noexcept
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_sub_ps(row[0], t), _mm_sub_ps(row[1], t), _mm_sub_ps(row[2], t), _mm_sub_ps(row[3], t) };
}

SIMD_Mat4f SIMD_Mat4f::operator*(float a) const noexcept
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_mul_ps(row[0], t), _mm_mul_ps(row[1], t), _mm_mul_ps(row[2], t), _mm_mul_ps(row[3], t) };
}

SIMD_Mat4f SIMD_Mat4f::operator/(float a) const noexcept
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_div_ps(row[0], t), _mm_div_ps(row[1], t), _mm_div_ps(row[2], t), _mm_div_ps(row[3], t) };
}

SIMD_Vec4f SIMD_Mat4f::operator*(const SIMD_Vec4f& vec) const noexcept
{
	return {
		util::SIMD::hadd(_mm_mul_ps(row[0], vec.row)),
		util::SIMD::hadd(_mm_mul_ps(row[1], vec.row)),
		util::SIMD::hadd(_mm_mul_ps(row[2], vec.row)),
		util::SIMD::hadd(_mm_mul_ps(row[3], vec.row))
	};
}

SIMD_Mat4f SIMD_Mat4f::operator+(const SIMD_Mat4f& that) const noexcept
{
	return {
		_mm_add_ps(row[0], that.row[0]),
		_mm_add_ps(row[1], that.row[1]),
		_mm_add_ps(row[2], that.row[2]),
		_mm_add_ps(row[3], that.row[3])
	};
}

SIMD_Mat4f SIMD_Mat4f::operator-(const SIMD_Mat4f& that) const noexcept
{
	return {
		_mm_sub_ps(row[0], that.row[0]),
		_mm_sub_ps(row[1], that.row[1]),
		_mm_sub_ps(row[2], that.row[2]),
		_mm_sub_ps(row[3], that.row[3])
	};
}

SIMD_Mat4f SIMD_Mat4f::operator*(const SIMD_Mat4f& that) const noexcept
{
	return {
		SIMD_Mat4f::mul_row_by_mat(row[0], that),
		SIMD_Mat4f::mul_row_by_mat(row[1], that),
		SIMD_Mat4f::mul_row_by_mat(row[2], that),
		SIMD_Mat4f::mul_row_by_mat(row[3], that)
	};
}

SIMD_Mat4f& SIMD_Mat4f::operator+=(float a) noexcept
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_add_ps(row[0], t);
	row[1] = _mm_add_ps(row[1], t);
	row[2] = _mm_add_ps(row[2], t);
	row[3] = _mm_add_ps(row[3], t);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator-=(float a) noexcept
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_sub_ps(row[0], t);
	row[1] = _mm_sub_ps(row[1], t);
	row[2] = _mm_sub_ps(row[2], t);
	row[3] = _mm_sub_ps(row[3], t);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator*=(float a) noexcept
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_mul_ps(row[0], t);
	row[1] = _mm_mul_ps(row[1], t);
	row[2] = _mm_mul_ps(row[2], t);
	row[3] = _mm_mul_ps(row[3], t);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator/=(float a) noexcept
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_div_ps(row[0], t);
	row[1] = _mm_div_ps(row[1], t);
	row[2] = _mm_div_ps(row[2], t);
	row[3] = _mm_div_ps(row[3], t);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator+=(const SIMD_Mat4f& that) noexcept
{
	row[0] = _mm_add_ps(row[0], that.row[0]);
	row[1] = _mm_add_ps(row[1], that.row[1]);
	row[2] = _mm_add_ps(row[2], that.row[2]);
	row[3] = _mm_add_ps(row[3], that.row[3]);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator-=(const SIMD_Mat4f& that) noexcept
{
	row[0] = _mm_sub_ps(row[0], that.row[0]);
	row[1] = _mm_sub_ps(row[1], that.row[1]);
	row[2] = _mm_sub_ps(row[2], that.row[2]);
	row[3] = _mm_sub_ps(row[3], that.row[3]);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::operator*=(const SIMD_Mat4f& that) noexcept
{
	row[0] = SIMD_Mat4f::mul_row_by_mat(row[0], that);
	row[1] = SIMD_Mat4f::mul_row_by_mat(row[1], that);
	row[2] = SIMD_Mat4f::mul_row_by_mat(row[2], that);
	row[3] = SIMD_Mat4f::mul_row_by_mat(row[3], that);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::unit() noexcept
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	row[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	row[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::orthographic(float left, float right, float bottom, float top, float near, float far) noexcept
{
	const float w = right - left;
	const float h = top - bottom;
	const float d = far - near;

	row[0] = _mm_set_ps(-(right + left) / w, 0.0f, 0.0f, 2 / w);
	row[1] = _mm_set_ps(-(top + bottom) / h, 0.0f, 2 / h, 0.0f);
	row[2] = _mm_set_ps(-(near + far) / d, 2 / d,   0.0f, 0.0f);
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::perspective(float fov, float ratio, float near, float far) noexcept
{
	const float tf = Algo::tan(Algo::to_rad(fov / 2.0f));
	const float rd = near - far;

	row[0] = _mm_set_ps(0.0f,                   0.0f,              0.0f,      1.0f / (ratio * tf));
	row[0] = _mm_set_ps(0.0f,                   0.0f,              1.0f / tf, 0.0f);
	row[0] = _mm_set_ps(2.0f * far * near / rd, (far + near) / rd, 0.0f,      0.0f);
	row[0] = _mm_set_ps(0.0f,                   -1.0f,             0.0f,      0.0f);
	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::translate(const SIMD_Vec4f& vec) noexcept
{
	//  TODO: remove
	/*data[3] = util::SIMD::hadd(_mm_mul_ps(vec.row, row[0]));
	data[7] = util::SIMD::hadd(_mm_mul_ps(vec.row, row[1]));
	data[11] = util::SIMD::hadd(_mm_mul_ps(vec.row, row[2]));
	data[15] = util::SIMD::hadd(_mm_mul_ps(vec.row, row[3]));
	*/
	data[3] += vec.x;
	data[7] += vec.y;
	data[11] += vec.z;
	return *this;
}

SIMD_Mat4f& SIMD_Mat4f::rot_x(float angle) noexcept
{
	return *this *= SIMD_Mat4f::get_rot_x(angle);
}

SIMD_Mat4f& SIMD_Mat4f::rot_y(float angle) noexcept
{
	return *this *= SIMD_Mat4f::get_rot_y(angle);
}

SIMD_Mat4f& SIMD_Mat4f::rot_z(float angle) noexcept
{
	return *this *= SIMD_Mat4f::get_rot_z(angle);
}

SIMD_Mat4f& SIMD_Mat4f::rot(const Vec3<float>& axis, float angle) noexcept
{
	return *this *= SIMD_Mat4f::get_rot(axis, angle);
}

SIMD_Mat4f& SIMD_Mat4f::look_at(const SIMD_Vec4f& pos, const SIMD_Vec4f& target, const SIMD_Vec4f& up) noexcept
{
	const SIMD_Vec4f camDir = (pos - target).normalize();
	const SIMD_Vec4f camRight = up.cross(camDir).normalize();
	const SIMD_Vec4f camUp = camDir.cross(camRight);

	row[0] = camRight.row;
	row[1] = camUp.row;
	row[2] = camDir.row;
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	return this->translate(pos);
}

}
