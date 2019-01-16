#ifndef __DK_AUDIO_CORE_H__
#define __DK_AUDIO_CORE_H__

#include <AL/alc.h>
#include "Status.h"

namespace dk::audio
{

class Core
{
private:
	static ALCdevice*  s_device;
	static ALCcontext* s_context;

public:
	static Status create() noexcept;
	static void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_CORE_H__
