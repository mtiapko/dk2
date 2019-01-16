#ifndef __DK_GRAPH_TEXTURE_DATA_H__
#define __DK_GRAPH_TEXTURE_DATA_H__

#include <stdint.h>
#include "Resource.h"

namespace dk::graph
{

class TextureData final: public Resource
{
private:
	uint8_t* m_data;
	uint32_t m_width;
	uint32_t m_height;
	uint8_t  m_red_bits;
	uint8_t  m_green_bits;
	uint8_t  m_blue_bits;
	uint8_t  m_alpha_bits;

public:
	TextureData() noexcept;
	~TextureData() noexcept override;

	static ResourceType type() noexcept { return ResourceType::TEXTURE_DATA; }

	uint8_t* data() const noexcept { return m_data; }
	uint32_t width() const noexcept { return m_width; }
	uint32_t height() const noexcept { return m_height; }
	uint8_t red_bits() const noexcept { return m_red_bits; }
	uint8_t green_bits() const noexcept { return m_green_bits; }
	uint8_t blue_bits() const noexcept { return m_blue_bits; }
	uint8_t alpha_bits() const noexcept { return m_alpha_bits; }

	void set_data(uint8_t* data) noexcept { m_data = data; }
	void set_width(uint32_t width) noexcept { m_width = width; }
	void set_height(uint32_t height) noexcept { m_height = height; }
	void set_red_bits(uint8_t red_bits) noexcept { m_red_bits = red_bits; }
	void set_green_bits(uint8_t green_bits) noexcept { m_green_bits = green_bits; }
	void set_blue_bits(uint8_t blue_bits) noexcept { m_blue_bits = blue_bits; }
	void set_alpha_bits(uint8_t alpha_bits) noexcept { m_alpha_bits = alpha_bits; }

	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_TEXTURE_DATA_H__
