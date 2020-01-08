#include <SOIL2.h>
#include "dk/containers/UniquePtr.h"
#include "dk/Mem.h"
#include "dk/Log.h"
#include "TextureImporter.h"

namespace gl
{

Status TextureImporter::import_texture_data(graph::TextureData* tex_data, StringView file_path) noexcept
{
	int width;
	int height;
	int channels;
	tex_data->data = SOIL_load_image(file_path.data(), &width, &height, &channels, SOIL_LOAD_AUTO);
	if (tex_data->data == nullptr) {
		DK_LOG_ERROR("SOIL failed to import texture '", file_path, "': ", SOIL_last_result());
		return Status::ERROR;
	}

	tex_data->width = width;
	tex_data->height = height;
	switch (channels) {
		case SOIL_LOAD_L:    tex_data->type = graph::TextureType::GRAY;       break;
		case SOIL_LOAD_LA:   tex_data->type = graph::TextureType::GRAY_ALPHA; break;
		case SOIL_LOAD_RGB:  tex_data->type = graph::TextureType::RGB;        break;
		case SOIL_LOAD_RGBA: tex_data->type = graph::TextureType::RGBA;       break;
		default:
			DK_LOG_ERROR("Unsupported texture type");
			return Status::ERROR;
	}

	DK_LOG_OK(
		"Texture data created from file '", file_path, "':\n"
		"\twidth x height: ", width, 'x', height, '\n',
		"\tcolor format:   ", graph::TextureTypeNames[(int)tex_data->type]
	);
	return Status::OK;
}

Status TextureImporter::import_texture(graph::Texture* texture, StringView file_path) noexcept
{
	graph::TextureData data;
	data.set_resource_creator(this);

	if (auto err = this->import_texture_data(&data, file_path); !err)
		return err;

	return texture->create_from_resource_data(&data);
}

Resource* TextureImporter::import(ResourceType type, StringView file_path) noexcept /* override */
{
	if (type == ResourceType::TEXTURE_DATA) {
		UniquePtr<graph::TextureData> data(dk_mem_new(graph::TextureData));
		if (auto err = this->import_texture_data(data.get(), file_path); !err)
			return nullptr;

		return (Resource*)data.release();
	} else if (type == ResourceType::TEXTURE) {
		auto texture_deleter = [](graph::Texture* texture) noexcept
			{ texture->resource_creator()->delete_resource(texture); };

		UniquePtr<graph::Texture, decltype(texture_deleter)>
			texture(Core::get().active<graph::Renderer>()->new_resource<graph::Texture>());
		if (auto err = this->import_texture(texture.get(), file_path); !err)
			return nullptr;

		return (Resource*)texture.release();
	}

	DK_LOG_ERROR("Unsupported resource type");
	return nullptr;
}

Status TextureImporter::import(Resource* res, StringView file_path) noexcept /* override */
{
	switch (res->resource_type()) {
		case ResourceType::TEXTURE_DATA: return this->import_texture_data((graph::TextureData*)res, file_path);
		case ResourceType::TEXTURE: return this->import_texture((graph::Texture*)res, file_path);
		default:
			DK_LOG_ERROR("Unsupported resource type");
			return Status::ERROR;
	}
}

void TextureImporter::delete_resource(Resource* res) noexcept /* override */
{
	res->destroy();
	dk_mem_delete(res);
}

}
