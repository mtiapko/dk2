#ifndef __DK_GRAPH_TEXTURE_DATA_H__
#define __DK_GRAPH_TEXTURE_DATA_H__

#include "dk/Resource.h"

namespace dk::graph
{

enum class TextureType
{
	GRAY = 0,
	GRAY_ALPHA,
	RGB,
	RGBA,

	TEXTURE_TYPE_SIZE
};

static constexpr StringView TextureTypeNames[(int)TextureType::TEXTURE_TYPE_SIZE] = {
	[(int)TextureType::GRAY]       = "GRAY",
	[(int)TextureType::GRAY_ALPHA] = "GRAY_ALPHA",
	[(int)TextureType::RGB]        = "RGB",
	[(int)TextureType::RGBA]       = "RGBA"
};

struct TextureData final : public Resource
{
	uint8_t*    data;
	uint16_t    width;
	uint16_t    height;
	TextureType type;

	DK_RESOURCE_TYPE_INFO(TEXTURE_DATA);
};

}

#endif // !__DK_GRAPH_TEXTURE_DATA_H__
