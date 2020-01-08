#include <GL/glew.h>
#include "Texture.h"
#include "Debug.h"

namespace gl
{

/* static */ Status Texture::to_gl_type(GLenum& gl_type, graph::TextureType type) noexcept
{
	switch (type) {
		case graph::TextureType::GRAY:       gl_type = GL_RG;   break;
		case graph::TextureType::GRAY_ALPHA: gl_type = GL_RED;  break;
		case graph::TextureType::RGB:        gl_type = GL_RGB;  break;
		case graph::TextureType::RGBA:       gl_type = GL_RGBA; break;
		default:
			DK_LOG_ERROR("Unsupported texture type");
			return Status::ERROR;
	}

	return Status::OK;
}

void Texture::enable(uint32_t tex_unit) noexcept /* override */
{
	GL_CALL(glActiveTexture(GL_TEXTURE0 + tex_unit));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::disable() noexcept /* override */
{
	// TODO:
	//GL_CALL(glActiveTexture(GL_TEXTURE0 + ...));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Status Texture::create() noexcept /* override */
{
	GLenum gl_type;
	auto tex_data = (graph::TextureData*)this->resource_data();
	if (auto err = to_gl_type(gl_type, tex_data->type); !err)
		return err;

	GL_CALL(glGenTextures(1, &m_id));
	this->enable(0);

	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, gl_type, tex_data->width,
		tex_data->height, 0, gl_type, GL_UNSIGNED_BYTE, tex_data->data));
	GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

	this->disable();
	return Status::OK;
}

void Texture::destroy() noexcept /* override */
{
	if (m_id != 0) {
		GL_CALL(glDeleteTextures(1, &m_id));
		m_id = 0;
	}
}

}
