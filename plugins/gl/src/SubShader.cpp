#include <GL/glew.h>
#include "SubShader.h"
#include "Debug.h"

namespace gl
{

/* static */ Status SubShader::convert_to_gl_type(GLenum& gl_type, graph::SubShaderType type) noexcept
{
	switch (type) {
		case graph::SubShaderType::VERTEX:   gl_type = GL_VERTEX_SHADER; break;
		case graph::SubShaderType::FRAGMENT: gl_type = GL_FRAGMENT_SHADER; break;
		default:
			DK_LOG_ERROR("Unsupported shader type");
			return Status::ERROR;
	}

	return Status::OK;
}

Status SubShader::create() noexcept /* override */
{
	GLenum gl_type;
	auto shader_data = (graph::SubShaderData*)this->resource_data();
	if (auto err = convert_to_gl_type(gl_type, shader_data->type); !err)
		return err;

	m_id = GL_CALL(glCreateShader(gl_type));
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader");
		return Status::ERROR;
	}

	auto src = shader_data->source.data();
	GLint len = shader_data->source.size();
	GL_CALL(glShaderSource(m_id, 1, &src, &len));
	GL_CALL(glCompileShader(m_id));

	GLint val;
	GL_CALL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetShaderInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to compile shader '",
			shader_data->file_path, "':\n\t", StringView(buff, val));
		return Status::ERROR;
	}

	DK_LOG_OK("Sub shader '", shader_data->file_path, "' created");
	return Status::OK;
}

void SubShader::destroy() noexcept /* override */
{
	if (m_id != 0) {
		GL_CALL(glDeleteShader(m_id));
		m_id = 0;
	}
}

}
