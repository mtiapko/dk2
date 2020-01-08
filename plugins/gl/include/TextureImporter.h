#ifndef __DK_GL_TEXTURE_IMPORTER_H__
#define __DK_GL_TEXTURE_IMPORTER_H__

#include "dk/graph/Texture.h"
#include "Common.h"

namespace gl
{

class TextureImporter final : public sys::ResourceImporter
{
private:
	Status import_texture_data(graph::TextureData* data, StringView file_path) noexcept;
	Status import_texture(graph::Texture* texture, StringView file_path) noexcept;

public:
	Resource* import(ResourceType type, StringView file_path) noexcept override;
	Status import(Resource* res, StringView file_path) noexcept override;

	void delete_resource(Resource* res) noexcept override;
};

}

#endif // !__DK_GL_TEXTURE_IMPORTER_H__
