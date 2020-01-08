#ifndef __DK_SYS_RESOURCE_CREATOR_H__
#define __DK_SYS_RESOURCE_CREATOR_H__

#include "dk/Resource.h"
#include "dk/Status.h"

namespace dk::sys
{

class ResourceCreator
{
public:
	virtual void delete_resource(Resource* res) noexcept = 0;
};

}

#endif // !__DK_SYS_RESOURCE_CREATOR_H__
