#include <GL/glew.h>
#include "graph/debug.h"
#include "graph/texture.h"

namespace dk::graph
{

texture::texture() noexcept
	: m_id(0)
{}

texture::~texture() noexcept /* override */
{
	this->destroy();
}

/* static */ GLenum texture::convert_to_gl_fmt(uint8_t red_bits,
	uint8_t green_bits, uint8_t blue_bits, uint8_t alpha_bits) noexcept
{
	(void)red_bits;
	(void)green_bits;
	(void)blue_bits;
	if (alpha_bits == 0)
		return GL_RGB;

	return GL_RGBA;
}

void texture::enable() const noexcept
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void texture::disable() const noexcept
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

status texture::create(const texture_data& data) noexcept
{
	GL_CALL(glGenTextures(1, &m_id));
	this->enable();
	GLenum format = convert_to_gl_fmt(data.red_bits(), data.green_bits(), data.blue_bits(), data.alpha_bits());
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, data.width(), data.height(), 0, format, GL_UNSIGNED_BYTE, data.data()));
	GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	this->disable();

	return status::OK;
}

void texture::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteTextures(1, &m_id));
		m_id = 0;
	}
}

}
