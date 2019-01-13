#include <SOIL2.h>
#include "sys/loaders/texture_loader.h"
#include "mem.h"
#include "log.h"

namespace dk::sys
{

status texture_loader::load(graph::texture_data& res, string_view file_path) noexcept
{
	int width;
	int height;
	int channels;
	unsigned char* data = SOIL_load_image(file_path.data(), &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr) {
		DK_LOG_ERROR("SOIL failed to load texture '", file_path, "': ", SOIL_last_result());
		return status::ERROR;
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

	return status::OK;
}

status texture_loader::load(graph::texture& res, string_view file_path) noexcept
{
	graph::texture_data texture_data;
	if (auto ret = load(texture_data, file_path); !ret)
		return ret;

	return res.create(texture_data);
}

resource* texture_loader::load(string_view file_path, resource_type type) noexcept /* override */
{
	if (type == resource_type::TEXTURE_DATA) {
		graph::texture_data* texture_data = mem_create(graph::texture_data);
		if (!load(*texture_data, file_path)) {
			mem_destroy(texture_data);
			return nullptr;
		}

		return texture_data;
	} else if (type == resource_type::TEXTURE) {
		graph::texture* texture = mem_create(graph::texture);
		if (!load(*texture, file_path)) {
			mem_destroy(texture);
			return nullptr;
		}

		return texture;
	}

	DK_LOG_ERROR("Texture loader does not support this resource type: #", (uint32_t)type);
	return nullptr;
}

status texture_loader::load(resource& res, string_view file_path, resource_type type) noexcept /* override */
{
	if (type == resource_type::TEXTURE_DATA) return load(static_cast<graph::texture_data&>(res), file_path);
	else if (type == resource_type::TEXTURE) return load(static_cast<graph::texture&>(res), file_path);

	DK_LOG_ERROR("Texture loader does not support this resource type: #", (uint32_t)type);
	return status::ERROR;
}

}
