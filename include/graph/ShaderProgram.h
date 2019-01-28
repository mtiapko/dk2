#ifndef __DK_GRAPH_SHADER_PROGRAM_H__
#define __DK_GRAPH_SHADER_PROGRAM_H__

#include "math/Mat.h"
#include "graph/Shader.h"
#include "graph/UniformLocation.h"

namespace dk::graph
{

class ShaderProgram final: public Resource
{
private:
	GLuint m_id;

public:
	ShaderProgram() noexcept;
	~ShaderProgram() noexcept override;

	void enable() const noexcept;
	void disable() const noexcept;

	Status uniform_location(StringView name, UniformLocation& location) const noexcept;

	Status set_uniform(UniformLocation location, const math::Mat4f& val) const noexcept;
	Status set_uniform(UniformLocation location, float val) const noexcept;

	Status add(StringView file_path, ShaderType type) const noexcept;
	Status add(const Shader& inst) const noexcept;
	Status remove_shaders() const noexcept;

	Status create() noexcept;
	Status link() const noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_PROGRAM_H__
