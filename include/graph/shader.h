#ifndef __DK_GRAPH_SHADER_H__
#define __DK_GRAPH_SHADER_H__

#include <GL/gl.h>
#include "graph/shader_data.h"

namespace dk::graph
{

enum class shader_type
{
	VERTEX = 0,
	GEOMETRY,
	FRAGMENT
};

class shader final: public resource
{
private:
	GLuint m_id;

	static GLenum convert_to_gl_type(shader_type type) noexcept;

public:
	shader() noexcept;
	~shader() noexcept override;

	GLuint id() const noexcept { return m_id; }

	status create(string_view file_path, shader_type type) noexcept;
	status create(const shader_data& data, shader_type type) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_H__
