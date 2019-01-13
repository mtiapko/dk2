#ifndef __DK_GRAPH_SHADER_PROGRAM_H__
#define __DK_GRAPH_SHADER_PROGRAM_H__

#include "graph/shader.h"

namespace dk::graph
{

class shader_program final: public resource
{
private:
	GLuint m_id;

public:
	shader_program() noexcept;
	~shader_program() noexcept override;

	void enable() const noexcept;
	void disable() const noexcept;

	status add(string_view file_path, shader_type type) const noexcept;
	status add(const shader& inst) const noexcept;
	status remove_shaders() const noexcept;

	status create() noexcept;
	status link() const noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_PROGRAM_H__
