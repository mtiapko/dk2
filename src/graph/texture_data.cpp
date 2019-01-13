#include <SOIL2.h>
#include "graph/texture_data.h"
#include "mem.h"

namespace dk::graph
{

texture_data::texture_data() noexcept
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_red_bits(0)
	, m_green_bits(0)
	, m_blue_bits(0)
{}

texture_data::~texture_data() noexcept /* override */
{
	this->destroy();
}

void texture_data::destroy() noexcept
{
	if (m_data != nullptr) {
		SOIL_free_image_data(m_data);
		m_data = nullptr;
	}
}

}
