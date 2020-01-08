#ifndef __DK_SYS_RESOURCE_OWNER_H__
#define __DK_SYS_RESOURCE_OWNER_H__

#include "dk/Resource.h"

namespace dk::sys
{

class ResourceOwner
{
public:
	virtual void remove_resource_slave(Resource* res) noexcept = 0;
};

}

#endif // !__DK_SYS_RESOURCE_OWNER_H__
