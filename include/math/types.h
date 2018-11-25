#ifndef __DK_TYPES_H__
#define __DK_TYPES_H__

#include "math/vec3.h"
#include "math/mat4f_SIMD.h"

namespace dk
{

using vec3f = vec3<float>;
using vec4f = vec4f_SIMD;
using mat4f = mat4f_SIMD;

}

#endif  //  !__DK_MATH_TYPES_H__
