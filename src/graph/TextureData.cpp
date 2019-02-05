#include <SOIL2.h>
#include "graph/TextureData.h"
#include "Mem.h"

namespace dk::graph
{

TextureData::TextureData(ResourceManager* res_mgr) noexcept
	: Resource(res_mgr)
	, m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_red_bits(0)
	, m_green_bits(0)
	, m_blue_bits(0)
	, m_alpha_bits(0)
{}

TextureData::~TextureData() noexcept /* override */
{
	this->destroy();
}

void TextureData::destroy() noexcept
{
	if (m_data != nullptr) {
		SOIL_free_image_data(m_data);
		m_data = nullptr;
	}
}

}
