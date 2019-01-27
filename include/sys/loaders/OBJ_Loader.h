#ifndef __DK_SYS_OBJ_LOADER_H__
#define __DK_SYS_OBJ_LOADER_H__

#include "graph/Model.h"
#include "sys/ResourceLoader.h"

namespace dk::sys
{

class OBJ_Loader final: public ResourceLoader
{
public:
	Status load(graph::ModelData& model_data, StringView file_path) noexcept;
	Status load(graph::Model& model, StringView file_path) noexcept;

	Resource* load(StringView file_path, ResourceType type) noexcept override;
	Status    load(Resource& res, StringView file_path, ResourceType type) noexcept override;
};

}

#endif  //  !__DK_SYS_OBJ_LOADER_H__
