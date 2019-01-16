#include <GL/glew.h>
#include "graph/Debug.h"
#include "graph/Shader.h"

namespace dk::graph
{

Shader::Shader() noexcept
	: m_id(0)
{}

Shader::~Shader() noexcept /* override */
{
	this->destroy();
}

/* static */ GLenum Shader::convert_to_gl_type(ShaderType type) noexcept
{
	switch (type) {
		case ShaderType::VERTEX:   return GL_VERTEX_SHADER;
		case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
		case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
	}

	DK_LOG_ERROR("Unsupported shader type");
	return 0;
}

Status Shader::create(StringView file_path, ShaderType type) noexcept
{
	ShaderData data;
	if (auto ret = data.create(file_path); !ret)
		return ret;

	return this->create(data, type);
}

Status Shader::create(const ShaderData& shader_data, ShaderType type) noexcept
{
	m_id = GL_CALL(glCreateShader(convert_to_gl_type(type)));
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader");
		return Status::ERROR;
	}

	auto src = shader_data.data().data(); /* triple! */
	GLint len = shader_data.data().size();
	GL_CALL(glShaderSource(m_id, 1, &src, &len));
	GL_CALL(glCompileShader(m_id));

	GLint val;
	GL_CALL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetShaderInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to compile shader '", shader_data.file_path(), "':\n\t", StringView(buff, val));
		return Status::ERROR;
	}

	DK_LOG_OK("Shader '", shader_data.file_path(), "' created");
	return Status::OK;
}

void Shader::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteShader(m_id));
		m_id = 0;
	}
}

}
