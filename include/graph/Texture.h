#ifndef __DK_GRAPH_TEXTURE_H__
#define __DK_GRAPH_TEXTURE_H__

#include <GL/gl.h>
#include "Status.h"
#include "graph/TextureData.h"

namespace dk::graph
{

class Texture final: public Resource
{
private:
	GLuint m_id;

public:
	Texture() noexcept;
	~Texture() noexcept override;

	static ResourceType type() noexcept { return ResourceType::TEXTURE; }
	static GLenum to_gl_fmt(uint8_t red_bits, uint8_t green_bits, uint8_t blue_bits, uint8_t alpha_bits) noexcept;
	static GLenum to_gl_fmt(const TextureData& data) noexcept;

	void enable() const noexcept;
	void disable() const noexcept;

	GLuint id() const noexcept { return m_id; }

	Status create(const TextureData& data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_TEXTURE_H__
