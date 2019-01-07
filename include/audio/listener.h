#ifndef __DK_AUDIO_LISTENER_H__
#define __DK_AUDIO_LISTENER_H__

#include "status.h"
#include "math/vec.h"

namespace dk::audio
{

class listener
{
public:
	static void set_gain(float val) noexcept;
	static void set_pos(math::vec3f val) noexcept;
	static void set_velocity(math::vec3f val) noexcept;
	static void set_orientation(math::vec3f dir, math::vec3f up) noexcept;

	static void set_orientation(const float orientation[]) noexcept;

	static status create() noexcept;
};

}

#endif  //  !__DK_AUDIO_LISTENER_H__
