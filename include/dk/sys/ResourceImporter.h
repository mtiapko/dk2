#ifndef __DK_SYS_RESOURCE_IMPORTER_H__
#define __DK_SYS_RESOURCE_IMPORTER_H__

#include "dk/containers/StringView.h"
#include "dk/sys/ResourceCreator.h"
#include "dk/Resource.h"
#include "dk/Status.h"

namespace dk::sys
{

class ResourceImporter : public ResourceCreator
{
public:
	virtual Resource* import(ResourceType type, StringView file_path) noexcept = 0;
	virtual Status import(Resource* res, StringView file_path) noexcept = 0;
};

}

#endif // !__DK_SYS_RESOURCE_IMPORTER_H__
