#ifndef __DK_AUDIO_CORE_H__
#define __DK_AUDIO_CORE_H__

#include <AL/alc.h>
#include "status.h"

namespace dk::audio
{

class core
{
private:
	static ALCdevice*  s_device;
	static ALCcontext* s_context;

public:
	static status create() noexcept;
};

}

#endif  //  !__DK_AUDIO_CORE_H__
