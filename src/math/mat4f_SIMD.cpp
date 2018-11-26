#include <cstring>
#include "math/mat4f_SIMD.h"

namespace dk
{

mat4f_SIMD::mat4f_SIMD(const mat4f_SIMD& other)
{
	row[0] = other.row[0];
	row[1] = other.row[1];
	row[2] = other.row[2];
	row[3] = other.row[3];
}

mat4f_SIMD::mat4f_SIMD(float data_[])
{
	row[0] = _mm_loadu_ps(data_);
	row[1] = _mm_loadu_ps(data_ + 4);
	row[2] = _mm_loadu_ps(data_ + 8);
	row[3] = _mm_loadu_ps(data_ + 12);
}

mat4f_SIMD::mat4f_SIMD(__m128 row_[])
{
	row[0] = _mm_load_ps((float*)row_);
	row[1] = _mm_load_ps((float*)(row_ + 1));
	row[2] = _mm_load_ps((float*)(row_ + 2));
	row[3] = _mm_load_ps((float*)(row_ + 3));
}

mat4f_SIMD::mat4f_SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3)
{
	row[0] = row0;
	row[1] = row1;
	row[2] = row2;
	row[3] = row3;
}

mat4f_SIMD::mat4f_SIMD(float e)
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, e);
	row[1] = _mm_set_ps(0.0f, 0.0f, e,    0.0f);
	row[2] = _mm_set_ps(0.0f, e,    0.0f, 0.0f);
	row[3] = _mm_set_ps(1.0f,    0.0f, 0.0f, 0.0f);
}

mat4f_SIMD::mat4f_SIMD(float e00, float e11, float e22, float e33 /* = 1.0f */)
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, e00);
	row[1] = _mm_set_ps(0.0f, 0.0f, e11,  0.0f);
	row[2] = _mm_set_ps(0.0f, e22,  0.0f, 0.0f);
	row[3] = _mm_set_ps(e33,  0.0f, 0.0f, 0.0f);
}

mat4f_SIMD::mat4f_SIMD(float e00, float e10, float e20, float e30,
	float e01, float e11, float e21, float e31,
	float e02, float e12, float e22, float e32,
	float e03, float e13, float e23, float e33)
{
	row[0] = _mm_set_ps(e30, e20, e10, e00);
	row[1] = _mm_set_ps(e31, e21, e11, e01);
	row[2] = _mm_set_ps(e32, e22, e12, e02);
	row[3] = _mm_set_ps(e33, e23, e13, e03);
}

mat4f_SIMD::mat4f_SIMD(vec4f_SIMD vec)
{
	row[0] = _mm_set_ps(0.0f,        0.0f,        0.0f,        vec.data[0]);
	row[1] = _mm_set_ps(0.0f,        0.0f,        vec.data[1], 0.0f);
	row[2] = _mm_set_ps(0.0f,        vec.data[2], 0.0f,        0.0f);
	row[3] = _mm_set_ps(vec.data[3], 0.0f,        0.0f,        0.0f);
}

mat4f_SIMD::mat4f_SIMD(vec4f_SIMD row0, vec4f_SIMD row1, vec4f_SIMD row2, vec4f_SIMD row3)
{
	row[0] = row0.row;
	row[1] = row1.row;
	row[2] = row2.row;
	row[3] = row3.row;
}

__m128 mat4f_SIMD::_s_mulRowByMat(const __m128& row, const mat4f_SIMD& mat)
{
	__m128 res = _mm_mul_ps(_mm_shuffle_ps(row, row, 0), mat.row[0]);
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (1u << 6) | (1u << 4) | (1u << 2u) | 1u), mat.row[1]));
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (2u << 6) | (2u << 4) | (2u << 2u) | 2u), mat.row[2]));
	res = _mm_add_ps(res, _mm_mul_ps(_mm_shuffle_ps(row, row, (3u << 6) | (3u << 4) | (3u << 2u) | 3u), mat.row[3]));

	return res;
}

mat4f_SIMD mat4f_SIMD::operator+(float a) const
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_add_ps(row[0], t), _mm_add_ps(row[1], t), _mm_add_ps(row[2], t), _mm_add_ps(row[3], t) };
}

mat4f_SIMD mat4f_SIMD::operator-(float a) const
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_sub_ps(row[0], t), _mm_sub_ps(row[1], t), _mm_sub_ps(row[2], t), _mm_sub_ps(row[3], t) };
}

mat4f_SIMD mat4f_SIMD::operator*(float a) const
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_mul_ps(row[0], t), _mm_mul_ps(row[1], t), _mm_mul_ps(row[2], t), _mm_mul_ps(row[3], t) };
}

mat4f_SIMD mat4f_SIMD::operator/(float a) const
{
	__m128 t = _mm_set1_ps(a);
	return { _mm_div_ps(row[0], t), _mm_div_ps(row[1], t), _mm_div_ps(row[2], t), _mm_div_ps(row[3], t) };
}

vec4f_SIMD mat4f_SIMD::operator*(const vec4f_SIMD& vec) const
{
	return {
		SIMD::hadd(_mm_mul_ps(row[0], vec.row)),
		SIMD::hadd(_mm_mul_ps(row[1], vec.row)),
		SIMD::hadd(_mm_mul_ps(row[2], vec.row)),
		SIMD::hadd(_mm_mul_ps(row[3], vec.row))
	};
}

mat4f_SIMD mat4f_SIMD::operator+(const mat4f_SIMD& other) const
{
	return {
		_mm_add_ps(row[0], other.row[0]),
		_mm_add_ps(row[1], other.row[1]),
		_mm_add_ps(row[2], other.row[2]),
		_mm_add_ps(row[3], other.row[3])
	};
}

mat4f_SIMD mat4f_SIMD::operator-(const mat4f_SIMD& other) const
{
	return {
		_mm_sub_ps(row[0], other.row[0]),
		_mm_sub_ps(row[1], other.row[1]),
		_mm_sub_ps(row[2], other.row[2]),
		_mm_sub_ps(row[3], other.row[3])
	};
}

mat4f_SIMD mat4f_SIMD::operator*(const mat4f_SIMD& other) const
{
	return {
		mat4f_SIMD::_s_mulRowByMat(row[0], other),
		mat4f_SIMD::_s_mulRowByMat(row[1], other),
		mat4f_SIMD::_s_mulRowByMat(row[2], other),
		mat4f_SIMD::_s_mulRowByMat(row[3], other)
	};
}

mat4f_SIMD& mat4f_SIMD::operator+=(float a)
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_add_ps(row[0], t);
	row[1] = _mm_add_ps(row[1], t);
	row[2] = _mm_add_ps(row[2], t);
	row[3] = _mm_add_ps(row[3], t);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator-=(float a)
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_sub_ps(row[0], t);
	row[1] = _mm_sub_ps(row[1], t);
	row[2] = _mm_sub_ps(row[2], t);
	row[3] = _mm_sub_ps(row[3], t);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator*=(float a)
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_mul_ps(row[0], t);
	row[1] = _mm_mul_ps(row[1], t);
	row[2] = _mm_mul_ps(row[2], t);
	row[3] = _mm_mul_ps(row[3], t);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator/=(float a)
{
	__m128 t = _mm_set1_ps(a);
	row[0] = _mm_div_ps(row[0], t);
	row[1] = _mm_div_ps(row[1], t);
	row[2] = _mm_div_ps(row[2], t);
	row[3] = _mm_div_ps(row[3], t);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator+=(const mat4f_SIMD& other)
{
	row[0] = _mm_add_ps(row[0], other.row[0]);
	row[1] = _mm_add_ps(row[1], other.row[1]);
	row[2] = _mm_add_ps(row[2], other.row[2]);
	row[3] = _mm_add_ps(row[3], other.row[3]);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator-=(const mat4f_SIMD& other)
{
	row[0] = _mm_sub_ps(row[0], other.row[0]);
	row[1] = _mm_sub_ps(row[1], other.row[1]);
	row[2] = _mm_sub_ps(row[2], other.row[2]);
	row[3] = _mm_sub_ps(row[3], other.row[3]);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator*=(const mat4f_SIMD& other)
{
	row[0] = mat4f_SIMD::_s_mulRowByMat(row[0], other);
	row[1] = mat4f_SIMD::_s_mulRowByMat(row[1], other);
	row[2] = mat4f_SIMD::_s_mulRowByMat(row[2], other);
	row[3] = mat4f_SIMD::_s_mulRowByMat(row[3], other);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::operator=(const mat4f_SIMD& other)
{
	row[0] = other.row[0];
	row[1] = other.row[1];
	row[2] = other.row[2];
	row[3] = other.row[3];

	return *this;
}

mat4f_SIMD& mat4f_SIMD::unit()
{
	row[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	row[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	row[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	return *this;
}

mat4f_SIMD& mat4f_SIMD::orthographic(float left, float right, float bottom, float top, float near, float far)
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

mat4f_SIMD& mat4f_SIMD::perspective(float fov, float ratio, float near, float far)
{
	const float tf = maths::tan(maths::to_rad(fov / 2.0f));
	const float rd = near - far;

	row[0] = _mm_set_ps(0.0f,                   0.0f,              0.0f,      1.0f / (ratio * tf));
	row[0] = _mm_set_ps(0.0f,                   0.0f,              1.0f / tf, 0.0f);
	row[0] = _mm_set_ps(2.0f * far * near / rd, (far + near) / rd, 0.0f,      0.0f);
	row[0] = _mm_set_ps(0.0f,                   -1.0f,             0.0f,      0.0f);
	return *this;
}

mat4f_SIMD& mat4f_SIMD::translate(const vec4f_SIMD& vec)
{
	//  TODO: remove
	/*data[3] = SIMD::hadd(_mm_mul_ps(vec.row, row[0]));
	data[7] = SIMD::hadd(_mm_mul_ps(vec.row, row[1]));
	data[11] = SIMD::hadd(_mm_mul_ps(vec.row, row[2]));
	data[15] = SIMD::hadd(_mm_mul_ps(vec.row, row[3]));
	*/
	data[3] += vec.data[0];
	data[7] += vec.data[1];
	data[11] += vec.data[2];
	return *this;
}

mat4f_SIMD& mat4f_SIMD::rot_x(float angle)
{
	return *this *= mat4f_SIMD::get_rot_x(angle);
}

mat4f_SIMD& mat4f_SIMD::rot_y(float angle)
{
	return *this *= mat4f_SIMD::get_rot_y(angle);
}

mat4f_SIMD& mat4f_SIMD::rot_z(float angle)
{
	return *this *= mat4f_SIMD::get_rot_z(angle);
}

mat4f_SIMD& mat4f_SIMD::rot(const vec3<float>& axis, float angle)
{
	return *this *= mat4f_SIMD::get_rot(axis, angle);
}

mat4f_SIMD& mat4f_SIMD::look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up)
{
	const vec4f_SIMD camDir = (pos - target).normalize();
	const vec4f_SIMD camRight = up.cross(camDir).normalize();
	const vec4f_SIMD camUp = camDir.cross(camRight);

	row[0] = camRight.row;
	row[1] = camUp.row;
	row[2] = camDir.row;
	row[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	return this->translate(pos);
}

mat4f_SIMD mat4f_SIMD::get_unit()
{
	return {
		_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f),
		_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
		_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_orthographic(float left, float right, float bottom, float top, float near, float far)
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

mat4f_SIMD mat4f_SIMD::get_perspective(float fov, float ratio, float near, float far)
{
	const float tf = maths::tan(maths::to_rad(fov / 2.0f));
	const float rd = near - far;

	return {
		_mm_set_ps(0.0f,                   0.0f,              0.0f,      1.0f / (ratio * tf)),
		_mm_set_ps(0.0f,                   0.0f,              1.0f / tf, 0.0f),
		_mm_set_ps(2.0f * far * near / rd, (far + near) / rd, 0.0f,      0.0f),
		_mm_set_ps(0.0f,                   -1.0f,             0.0f,      0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_translate(const vec4f_SIMD& vec)
{
	return {
		_mm_set_ps(vec.data[0], 0.0f, 0.0f, 1.0f),
		_mm_set_ps(vec.data[1], 0.0f, 1.0f, 0.0f),
		_mm_set_ps(vec.data[2], 1.0f, 0.0f, 0.0f),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_rot_x(float angle)
{
	const float sinv = maths::sin(maths::to_rad(angle));
	const float cosv = maths::cos(maths::to_rad(angle));

	return {
		_mm_set_ps(0.0f, 0.0f,  0.0f, 1.0f),
		_mm_set_ps(0.0f, -sinv, cosv, 0.0f),
		_mm_set_ps(0.0f, cosv,  sinv, 0.0f),
		_mm_set_ps(1.0f, 0.0f,  0.0f, 0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_rot_y(float angle)
{
	const float sinv = maths::sin(maths::to_rad(angle));
	const float cosv = maths::cos(maths::to_rad(angle));

	return {
		_mm_set_ps(0.0f, sinv, 0.0f, cosv),
		_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
		_mm_set_ps(0.0f, cosv, 0.0f, -sinv),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_rot_z(float angle)
{
	const float sinv = maths::sin(maths::to_rad(angle));
	const float cosv = maths::cos(maths::to_rad(angle));

	return {
		_mm_set_ps(0.0f, 0.0f, -sinv, cosv),
		_mm_set_ps(0.0f, 0.0f, cosv,  sinv),
		_mm_set_ps(0.0f, 1.0f, 0.0f,  0.0f),
		_mm_set_ps(1.0f, 0.0f, 0.0f,  0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_rot(const vec3<float>& axis, float angle)
{
	union
	{
		float data[4];
		__m128 simd;
	} tmp;

	const float sinv = maths::sin(maths::to_rad(angle));
	const float cosv = maths::cos(maths::to_rad(angle));
	__m128 axisv = _mm_set_ps(0.0f, axis.z, axis.y, axis.x);
	__m128 rcosv = _mm_set1_ps(1.0f - cosv);
	__m128 t = _mm_mul_ps(axisv, rcosv);

	//  0: x * sin
	//  1: y * sin
	//  2: z * sin
	tmp.simd = _mm_mul_ps(axisv, _mm_set1_ps(sinv));

	return {
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.x)), _mm_set_ps(0.0f, tmp.data[1], -tmp.data[2], cosv)),
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.y)), _mm_set_ps(0.0f, -tmp.data[0], cosv,        tmp.data[2])),
		_mm_add_ps(_mm_mul_ps(t, _mm_set1_ps(axis.z)), _mm_set_ps(0.0f, cosv,        tmp.data[0], -tmp.data[1])),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};
}

mat4f_SIMD mat4f_SIMD::get_look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up)
{
	const vec4f_SIMD camDir = (pos - target).normalize();
	const vec4f_SIMD camRight = up.cross(camDir).normalize();
	const vec4f_SIMD camUp = camDir.cross(camRight);

	return mat4f_SIMD {
		//camRight.row,
		//camUp.row,
		//camDir.row,
		_mm_set_ps(0.0f, camDir.data[0], camUp.data[0], camRight.data[0]),
		_mm_set_ps(0.0f, camDir.data[1], camUp.data[1], camRight.data[1]),
		_mm_set_ps(0.0f, camDir.data[2], camUp.data[2], camRight.data[2]),
		_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
	};//.translate(pos);
}

}
