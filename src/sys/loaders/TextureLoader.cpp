#include <SOIL2.h>
#include "sys/loaders/TextureLoader.h"
#include "Mem.h"
#include "Log.h"

namespace dk::sys
{

Status TextureLoader::load(graph::TextureData& res, StringView file_path) noexcept
{
	int width;
	int height;
	int channels;
	unsigned char* data = SOIL_load_image(file_path.data(), &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr) {
		DK_LOG_ERROR("SOIL failed to load texture '", file_path, "': ", SOIL_last_result());
		return Status::ERROR;
	}

	res.set_data(data);
	res.set_width(width);
	res.set_height(height);
	res.set_red_bits(8);

	if (channels == SOIL_LOAD_RGB || channels == SOIL_LOAD_RGBA) {
		res.set_green_bits(8);
		res.set_blue_bits(8);
	}

	if (channels == SOIL_LOAD_LA || channels == SOIL_LOAD_RGBA)
		res.set_alpha_bits(8);

	DK_LOG_OK(
		"Texture data created from file '", file_path, "':\n"
		"\twidth x height: ", width, 'x', height, '\n',
		"\tcolor format:   ",
			'R', (int)res.red_bits(),
			'G', (int)res.green_bits(),
			'B', (int)res.blue_bits(),
			'A', (int)res.alpha_bits()
	);

	return Status::OK;
}

Status TextureLoader::load(graph::Texture& res, StringView file_path) noexcept
{
	graph::TextureData texture_data;
	if (auto ret = load(texture_data, file_path); !ret)
		return ret;

	return res.create(texture_data);
}

Resource* TextureLoader::load(StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::TEXTURE_DATA) {
		graph::TextureData* texture_data = mem_create(graph::TextureData);
		if (!load(*texture_data, file_path)) {
			mem_destroy(texture_data);
			return nullptr;
		}

		return texture_data;
	} else if (type == ResourceType::TEXTURE) {
		graph::Texture* texture = mem_create(graph::Texture);
		if (!load(*texture, file_path)) {
			mem_destroy(texture);
			return nullptr;
		}

		return texture;
	}

	DK_LOG_ERROR("Texture loader does not support this resource type: #", (uint32_t)type);
	return nullptr;
}

Status TextureLoader::load(Resource& res, StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::TEXTURE_DATA) return load(static_cast<graph::TextureData&>(res), file_path);
	else if (type == ResourceType::TEXTURE) return load(static_cast<graph::Texture&>(res), file_path);

	DK_LOG_ERROR("Texture loader does not support this resource type: #", (uint32_t)type);
	return Status::ERROR;
}

}
