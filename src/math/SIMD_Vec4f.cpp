#include "math/Algo.h"
#include "math/SIMD_Vec4f.h"

namespace dk::math
{

SIMD_Vec4f::SIMD_Vec4f(const SIMD_Vec4f& that) noexcept
	: row(that.row)
{}

SIMD_Vec4f::SIMD_Vec4f(float data_[]) noexcept
	: row(_mm_loadu_ps(data_))
{}

SIMD_Vec4f::SIMD_Vec4f(__m128 row_[]) noexcept
	: row(_mm_load_ps((float*)row_))
{}

SIMD_Vec4f::SIMD_Vec4f(float a) noexcept
	: row(_mm_set1_ps(a))
{}

SIMD_Vec4f::SIMD_Vec4f(float x, float y, float z, float w /* = 0 */) noexcept
	: row(_mm_set_ps(w, z, y, x))
{}

SIMD_Vec4f::SIMD_Vec4f(__m128 row_) noexcept
	: row(row_)
{}

SIMD_Vec4f SIMD_Vec4f::operator+(float a) const noexcept
{
	return { _mm_add_ps(row, _mm_set1_ps(a)) };
}

SIMD_Vec4f SIMD_Vec4f::operator-(float a) const noexcept
{
	return { _mm_sub_ps(row, _mm_set1_ps(a)) };
}

SIMD_Vec4f SIMD_Vec4f::operator*(float a) const noexcept
{
	return { _mm_mul_ps(row, _mm_set1_ps(a)) };
}

SIMD_Vec4f SIMD_Vec4f::operator/(float a) const noexcept
{
	return { _mm_div_ps(row, _mm_set1_ps(a)) };
}

SIMD_Vec4f SIMD_Vec4f::operator+(const SIMD_Vec4f& that) const noexcept
{
	return { _mm_add_ps(row, that.row) };
}

SIMD_Vec4f SIMD_Vec4f::operator-(const SIMD_Vec4f& that) const noexcept
{
	return { _mm_sub_ps(row, that.row) };
}

SIMD_Vec4f& SIMD_Vec4f::operator+=(float a) noexcept
{
	row = _mm_add_ps(row, _mm_set1_ps(a));
	return *this;
}

SIMD_Vec4f& SIMD_Vec4f::operator-=(float a) noexcept
{
	row = _mm_sub_ps(row, _mm_set1_ps(a));
	return *this;
}

SIMD_Vec4f& SIMD_Vec4f::operator*=(float a) noexcept
{
	row = _mm_mul_ps(row, _mm_set1_ps(a));
	return *this;
}

SIMD_Vec4f& SIMD_Vec4f::operator/=(float a) noexcept
{
	row = _mm_div_ps(row, _mm_set1_ps(a));
	return *this;
}

SIMD_Vec4f& SIMD_Vec4f::operator+=(const SIMD_Vec4f& that) noexcept
{
	row = _mm_add_ps(row, that.row);
	return *this;
}

SIMD_Vec4f& SIMD_Vec4f::operator-=(const SIMD_Vec4f& that) noexcept
{
	row = _mm_add_ps(row, that.row);
	return *this;
}

float SIMD_Vec4f::dot(const SIMD_Vec4f& that) const noexcept
{
	return util::SIMD::hadd(_mm_mul_ps(row, that.row));
}

SIMD_Vec4f SIMD_Vec4f::cross(const SIMD_Vec4f& that) const noexcept
{
	#define SHUFFLE(src, x, y, z, w) _mm_shuffle_ps(src, src, (x << 6u) | (y << 4u) | (z << 2u) | w)

	constexpr unsigned X = 0;
	constexpr unsigned Y = 1;
	constexpr unsigned Z = 2;
	constexpr unsigned W = 3;

	return { _mm_sub_ps(
		_mm_mul_ps(SHUFFLE(row, Y, Z, X, W), SHUFFLE(that.row, Z, X, Y, W)),
		_mm_mul_ps(SHUFFLE(row, Z, X, Y, W), SHUFFLE(that.row, Y, Z, X, W)))
	};
}

float SIMD_Vec4f::length() const noexcept
{
	return Algo::sqrt(util::SIMD::hadd(_mm_mul_ps(row, row)));
}

SIMD_Vec4f& SIMD_Vec4f::normalize() noexcept
{
	const float rlen = 1 / this->length();
	row = _mm_mul_ps(row, _mm_set1_ps(rlen));
	return *this;
}

float* SIMD_Vec4f::begin() noexcept
{
	return &x;
}

float* SIMD_Vec4f::end() noexcept
{
	return &w + 1;
}

const float* SIMD_Vec4f::begin() const noexcept
{
	return &x;
}

const float* SIMD_Vec4f::end() const noexcept
{
	return &w + 1;
}

}
