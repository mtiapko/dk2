#ifndef __DK_GL_SHADER_H__
#define __DK_GL_SHADER_H__

#include "dk/graph/Shader.h"
#include "SubShader.h"
#include "Texture.h"

namespace gl
{

class Shader final : public graph::Shader
{
private:
	GLuint m_id = 0;
	Vector<Pair<graph::ShaderParamID, GLint>> m_params;

public:
	Shader(class Renderer* renderer) noexcept { this->set_resource_creator((sys::ResourceCreator*)renderer); }
	~Shader() noexcept override { this->destroy(); }

	void enable() noexcept override;
	void disable() noexcept override;

	void set_arg(GLint id, int data) noexcept;
	void set_arg(GLint id, float data) noexcept;
	void set_arg(GLint id, const math::Vec2f& data) noexcept;
	void set_arg(GLint id, const math::Vec3f& data) noexcept;
	void set_arg(GLint id, const math::Vec4f& data) noexcept;
	void set_arg(GLint id, const math::Mat4f& data) noexcept;
	void set_arg(graph::ShaderParamID param_id, const graph::ShaderArg& arg) noexcept override;

	Status add_param(const String& name, graph::ShaderParamID param_id) noexcept override;

	Status create() noexcept override;
	void destroy() noexcept override;
};

}

#endif // !__DK_GL_SHADER_H__
