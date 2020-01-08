#ifndef __DK_GL_SUB_SHADER_H__
#define __DK_GL_SUB_SHADER_H__

#include <GL/gl.h>
#include "dk/graph/SubShader.h"
#include "Common.h"

namespace gl
{

class SubShader final : public graph::SubShader
{
private:
	static Status convert_to_gl_type(GLenum& gl_type, graph::SubShaderType type) noexcept;

	GLuint m_id = 0;

public:
	SubShader(class Renderer* renderer) noexcept { this->set_resource_creator((sys::ResourceCreator*)renderer); }
	~SubShader() noexcept override { this->destroy(); }

	GLuint id() const noexcept { return m_id; }

	Status create() noexcept override;
	void destroy() noexcept override;
};

}

#endif // !__DK_GL_SUB_SHADER_H__
