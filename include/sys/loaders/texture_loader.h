#ifndef __DK_SYS_TEXTURE_LOADER_H__
#define __DK_SYS_TEXTURE_LOADER_H__

#include "graph/texture.h"
#include "sys/resource_loader.h"

namespace dk::sys
{

class texture_loader final: public resource_loader
{
public:
	status load(graph::texture_data& res, string_view file_path) noexcept;
	status load(graph::texture& res, string_view file_path) noexcept;

	resource* load(string_view file_path, resource_type type) noexcept override;
	status    load(resource& res, string_view file_path, resource_type type) noexcept override;
};

}

#endif  //  !__DK_SYS_TEXTURE_LOADER_H__
