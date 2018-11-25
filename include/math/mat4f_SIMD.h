#ifndef __DK_MAT4F_SIMD_H__
#define __DK_MAT4F_SIMD_H__

#include "math/vec4f_SIMD.h"

namespace dk
{

class mat4f_SIMD
{
private:
	static inline __m128 _s_mulRowByMat(const __m128& row, const mat4f_SIMD& mat);

public:
	union
	{
		float  data[4 * 4];
		__m128 row[4];
	};

	mat4f_SIMD() = default;
	mat4f_SIMD(const mat4f_SIMD& other);
	mat4f_SIMD(float data_[]);
	mat4f_SIMD(__m128 row[]);
	mat4f_SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3);
	mat4f_SIMD(float e);
	mat4f_SIMD(float e00, float e11, float e22, float e33 = 1.0f);
	mat4f_SIMD(float e00, float e10, float e20, float e30,
		float e01, float e11, float e21, float e31,
		float e02, float e12, float e22, float e32,
		float e03, float e13, float e23, float e33);
	mat4f_SIMD(vec4f_SIMD vec);
	mat4f_SIMD(vec4f_SIMD row0, vec4f_SIMD row1, vec4f_SIMD row2, vec4f_SIMD row3);

	mat4f_SIMD operator+(float a) const;
	mat4f_SIMD operator-(float a) const;
	mat4f_SIMD operator*(float a) const;
	mat4f_SIMD operator/(float a) const;

	vec4f_SIMD operator*(const vec4f_SIMD& vec) const;

	mat4f_SIMD operator+(const mat4f_SIMD& other) const;
	mat4f_SIMD operator-(const mat4f_SIMD& other) const;
	mat4f_SIMD operator*(const mat4f_SIMD& other) const;

	mat4f_SIMD& operator+=(float a);
	mat4f_SIMD& operator-=(float a);
	mat4f_SIMD& operator*=(float a);
	mat4f_SIMD& operator/=(float a);

	mat4f_SIMD& operator+=(const mat4f_SIMD& other);
	mat4f_SIMD& operator-=(const mat4f_SIMD& other);
	mat4f_SIMD& operator*=(const mat4f_SIMD& other);

	mat4f_SIMD& operator=(const mat4f_SIMD& other);

	mat4f_SIMD& unit();
	mat4f_SIMD& orthographic(float left, float right, float bottom, float top, float near, float far);
	mat4f_SIMD& perspective(float fov, float ratio, float near, float far);

	mat4f_SIMD& translate(const vec4f_SIMD& vec);

	mat4f_SIMD& rot_x(float angle);
	mat4f_SIMD& rot_y(float angle);
	mat4f_SIMD& rot_z(float angle);
	mat4f_SIMD& rot(const vec3<float>& axis, float angle);

	mat4f_SIMD& look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up);

	static mat4f_SIMD get_unit();
	static mat4f_SIMD get_orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4f_SIMD get_perspective(float fov, float ratio, float near, float far);

	static mat4f_SIMD get_translate(const vec4f_SIMD& vec);

	static mat4f_SIMD get_rot_x(float angle);
	static mat4f_SIMD get_rot_y(float angle);
	static mat4f_SIMD get_rot_z(float angle);
	static mat4f_SIMD get_rot(const vec3<float>& axis, float angle);

	static mat4f_SIMD get_look_at(const vec4f_SIMD& pos, const vec4f_SIMD& target, const vec4f_SIMD& up);
};

}

#endif  //  !__DK_MAT4F_SIMD_H__
