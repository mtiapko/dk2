#include "math/vec4f_SIMD.h"

namespace dk
{

vec4f_SIMD::vec4f_SIMD(const vec4f_SIMD& other)
	: row(other.row)
{}

vec4f_SIMD::vec4f_SIMD(float data_[])
	: row(_mm_loadu_ps(data_))
{}

vec4f_SIMD::vec4f_SIMD(__m128 row_[])
	: row(_mm_load_ps((float*)row_))
{}

vec4f_SIMD::vec4f_SIMD(float a)
	: row(_mm_set1_ps(a))
{}

vec4f_SIMD::vec4f_SIMD(float x, float y, float z, float w /* = 0 */)
	: row(_mm_set_ps(w, z, y, x))
{}

vec4f_SIMD::vec4f_SIMD(__m128 row_)
	: row(row_)
{}

vec4f_SIMD vec4f_SIMD::operator+(float a) const
{
	return { _mm_add_ps(row, _mm_set1_ps(a)) };
}

vec4f_SIMD vec4f_SIMD::operator-(float a) const
{
	return { _mm_sub_ps(row, _mm_set1_ps(a)) };
}

vec4f_SIMD vec4f_SIMD::operator*(float a) const
{
	return { _mm_mul_ps(row, _mm_set1_ps(a)) };
}

vec4f_SIMD vec4f_SIMD::operator/(float a) const
{
	return { _mm_div_ps(row, _mm_set1_ps(a)) };
}

vec4f_SIMD vec4f_SIMD::operator+(const vec4f_SIMD& other) const
{
	return { _mm_add_ps(row, other.row) };
}

vec4f_SIMD vec4f_SIMD::operator-(const vec4f_SIMD& other) const
{
	return { _mm_sub_ps(row, other.row) };
}

vec4f_SIMD& vec4f_SIMD::operator+=(float a)
{
	row = _mm_add_ps(row, _mm_set1_ps(a));
	return *this;
}

vec4f_SIMD& vec4f_SIMD::operator-=(float a)
{
	row = _mm_sub_ps(row, _mm_set1_ps(a));
	return *this;
}

vec4f_SIMD& vec4f_SIMD::operator*=(float a)
{
	row = _mm_mul_ps(row, _mm_set1_ps(a));
	return *this;
}

vec4f_SIMD& vec4f_SIMD::operator/=(float a)
{
	row = _mm_div_ps(row, _mm_set1_ps(a));
	return *this;
}

vec4f_SIMD& vec4f_SIMD::operator+=(const vec4f_SIMD& other)
{
	row = _mm_add_ps(row, other.row);
	return *this;
}

vec4f_SIMD& vec4f_SIMD::operator-=(const vec4f_SIMD& other)
{
	row = _mm_add_ps(row, other.row);
	return *this;
}

float vec4f_SIMD::dot(const vec4f_SIMD& other) const
{
	return SIMD::hadd(_mm_mul_ps(row, other.row));
}

vec4f_SIMD vec4f_SIMD::cross(const vec4f_SIMD& other) const
{
	#define SHUFFLE(src, x, y, z, w) _mm_shuffle_ps(src, src, (x << 6u) | (y << 4u) | (z << 2u) | w)

	constexpr unsigned X = 0;
	constexpr unsigned Y = 1;
	constexpr unsigned Z = 2;
	constexpr unsigned W = 3;

	return { _mm_sub_ps(
		_mm_mul_ps(SHUFFLE(row, Y, Z, X, W), SHUFFLE(other.row, Z, X, Y, W)),
		_mm_mul_ps(SHUFFLE(row, Z, X, Y, W), SHUFFLE(other.row, Y, Z, X, W)))
	};
}

float vec4f_SIMD::length() const
{
	return maths::sqrt(SIMD::hadd(_mm_mul_ps(row, row)));
}

vec4f_SIMD& vec4f_SIMD::normalize()
{
	const float rlen = 1 / this->length();
	row = _mm_mul_ps(row, _mm_set1_ps(rlen));
	return *this;
}

float* vec4f_SIMD::begin()
{
	return data;
}

float* vec4f_SIMD::end()
{
	return data + sizeof(data) / sizeof(data[0]);
}

const float* vec4f_SIMD::begin() const
{
	return data;
}

const float* vec4f_SIMD::end() const
{
	return data + sizeof(data) / sizeof(data[0]);
}

}
