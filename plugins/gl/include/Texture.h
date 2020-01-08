#ifndef __DK_GL_TEXTURE_H__
#define __DK_GL_TEXTURE_H__

#include <GL/gl.h>
#include "dk/graph/Texture.h"
#include "Common.h"

namespace gl
{

class Texture final : public graph::Texture
{
private:
	static Status to_gl_type(GLenum& gl_type, graph::TextureType type) noexcept;

	GLuint m_id = 0;

public:
	Texture(class Renderer* renderer) noexcept { this->set_resource_creator((sys::ResourceCreator*)renderer); }
	~Texture() noexcept override { this->destroy(); }

	void enable(uint32_t tex_unit) noexcept override;
	void disable() noexcept override;

	GLuint id() const noexcept { return m_id; }

	Status create() noexcept override;
	void destroy() noexcept override;
};

}

#endif // !__DK_GL_TEXTURE_H__
