#ifndef __DK_SYS_RESOURCE_LOADER_H__
#define __DK_SYS_RESOURCE_LOADER_H__

#include "resource.h"
#include "containers/string_view.h"

namespace dk::sys
{

class resource_loader
{
private:
	static hash_table<string, > s_loaders;

public:
	static resource_type get_type(string_view file_path) noexcept;
	static resource* load(string_view file_path, resource_type type = resource_type::AUTO) noexcept;

	static status load(string_view file_path, audio::sound_data& data) noexcept;
};

}

#endif  //  !__DK_SYS_RESOURCE_LOADER_H__
