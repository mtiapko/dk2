#ifndef __DK_SYS_TEXTURE_LOADER_H__
#define __DK_SYS_TEXTURE_LOADER_H__

#include "graph/Texture.h"
#include "sys/ResourceLoader.h"

namespace dk::sys
{

class TextureLoader final: public ResourceLoader
{
public:
	Status load(graph::TextureData& res, StringView file_path) noexcept;
	Status load(graph::Texture& res, StringView file_path) noexcept;

	Resource* load(StringView file_path, ResourceType type) noexcept override;
	Status    load(Resource& res, StringView file_path, ResourceType type) noexcept override;
};

}

#endif  //  !__DK_SYS_TEXTURE_LOADER_H__
