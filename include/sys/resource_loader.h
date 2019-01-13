#ifndef __DK_SYS_RESOURCE_LOADER_H__
#define __DK_SYS_RESOURCE_LOADER_H__

#include "resource.h"
#include "containers/string_view.h"

namespace dk::sys
{

class resource_loader
{
public:
	virtual ~resource_loader() noexcept = default;

	virtual resource* load(string_view file_path, resource_type type) noexcept = 0;
};

}

#endif  //  !__DK_SYS_RESOURCE_LOADER_H__
