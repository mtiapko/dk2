#ifndef __DK_SYS_RESOURCE_LOADER_H__
#define __DK_SYS_RESOURCE_LOADER_H__

#include "Status.h"
#include "Resource.h"
#include "containers/StringView.h"

namespace dk::sys
{

class ResourceLoader
{
public:
	virtual ~ResourceLoader() noexcept = default;

	virtual Resource* load(StringView file_path, ResourceType type) noexcept = 0;
	virtual Status    load(Resource& res, StringView file_path, ResourceType type) noexcept = 0;
};

}

#endif  //  !__DK_SYS_RESOURCE_LOADER_H__
