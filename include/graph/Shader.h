#ifndef __DK_GRAPH_SHADER_H__
#define __DK_GRAPH_SHADER_H__

#include <GL/gl.h>
#include "graph/ShaderData.h"

namespace dk::graph
{

enum class ShaderType
{
	VERTEX = 0,
	GEOMETRY,
	FRAGMENT
};

class Shader final: public Resource
{
private:
	GLuint m_id;

	static GLenum convert_to_gl_type(ShaderType type) noexcept;

public:
	Shader() noexcept;
	~Shader() noexcept override;

	static ResourceType type() noexcept { return ResourceType::SHADER; }

	GLuint id() const noexcept { return m_id; }

	Status create(StringView file_path, ShaderType type) noexcept;
	Status create(const ShaderData& data, ShaderType type) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_H__
