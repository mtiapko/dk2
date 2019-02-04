#include <GL/glew.h>
#include "graph/Debug.h"
#include "graph/Texture.h"

namespace dk::graph
{

Texture::Texture() noexcept
	: m_id(0)
{}

Texture::~Texture() noexcept /* override */
{
	this->destroy();
}

/* static */ GLenum Texture::to_gl_fmt(uint8_t red_bits,
	uint8_t green_bits, uint8_t blue_bits, uint8_t alpha_bits) noexcept
{
	(void)red_bits;
	(void)green_bits;
	(void)blue_bits;
	if (alpha_bits == 0)
		return GL_RGB;

	return GL_RGBA;
}

/* static */ GLenum Texture::to_gl_fmt(const TextureData& data) noexcept
{
	return to_gl_fmt(data.red_bits(), data.green_bits(), data.blue_bits(), data.alpha_bits());
}

void Texture::enable() const noexcept
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::disable() const noexcept
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Status Texture::create(const TextureData& data) noexcept
{
	GL_CALL(glGenTextures(1, &m_id));
	this->enable();
	GLenum format = to_gl_fmt(data);
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, data.width(), data.height(), 0, format, GL_UNSIGNED_BYTE, data.data()));
	GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	this->disable();

	return Status::OK;
}

void Texture::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteTextures(1, &m_id));
		m_id = 0;
	}
}

}
