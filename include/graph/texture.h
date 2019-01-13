#ifndef __DK_GRAPH_TEXTURE_H__
#define __DK_GRAPH_TEXTURE_H__

#include <GL/gl.h>
#include "status.h"
#include "graph/texture_data.h"

namespace dk::graph
{

class texture final: public resource
{
private:
	GLuint m_id;

	static GLenum convert_to_gl_fmt(uint8_t red_bits, uint8_t green_bits, uint8_t blue_bits, uint8_t alpha_bits) noexcept;

public:
	texture() noexcept;
	~texture() noexcept override;

	static resource_type type() noexcept { return resource_type::TEXTURE; }

	void enable() const noexcept;
	void disable() const noexcept;

	GLuint id() const noexcept { return m_id; }

	status create(const texture_data& data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_TEXTURE_H__
