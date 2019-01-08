#ifndef __DK_RESOURCE_H__
#define __DK_RESOURCE_H__

#include "status.h"

namespace dk
{

enum class resource_type
{
	AUTO = 0,
	UNKNOWN,
	AUDIO_DATA,
	TEXTURE_DATA,
	MESH_DATA,  //  TODO: is it possible (is it needed) to load only mesh?
	MODEL_DATA
};

class resource
{
public:
	virtual ~resource() noexcept = default;
};

}

#endif  //  !__DK_RESOURCE_H__
