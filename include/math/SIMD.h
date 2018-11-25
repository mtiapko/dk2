#ifndef __DK_SIMD_H__
#define __DK_SIMD_H__

#if defined(__SSE3__)
#	include <pmmintrin.h>
#elif defined(__SSE2__)
#	include <emmintrin.h>
#elif defined(__SSE__)
#	include <xmmintrin.h>
#else
#	error Platform does not support SSE
#endif

namespace dk
{

class SIMD
{
public:
	static inline float hadd(const __m128& t)
	{
		#if defined(__SSE3__)
			__m128 t0 = _mm_hadd_ps(t, t);
			return _mm_cvtss_f32(_mm_hadd_ps(t0, t0));
		#elif defined(__SSE__)
			__m128 t0 = _mm_add_ps(t, _mm_movehl_ps(t, t));
			__m128 t1 = _mm_shuffle_ps(t0, t0, 1);
			return _mm_cvtss_f32(_mm_add_ss(t0, t1));
		#endif
	}
};

}

#endif  //  !__DK_SIMD_H__
