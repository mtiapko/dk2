#ifndef __DK_AUDIO_LISTENER_H__
#define __DK_AUDIO_LISTENER_H__

#include "Status.h"
#include "math/Vec.h"

namespace dk::audio
{

class Listener
{
public:
	static void set_gain(float val) noexcept;
	static void set_pos(math::Vec3f val) noexcept;
	static void set_velocity(math::Vec3f val) noexcept;
	static void set_orientation(math::Vec3f dir, math::Vec3f up) noexcept;

	static void set_orientation(const float orientation[]) noexcept;

	static Status create() noexcept;
};

}

#endif  //  !__DK_AUDIO_LISTENER_H__
