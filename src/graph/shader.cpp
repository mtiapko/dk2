#include <GL/glew.h>
#include "graph/debug.h"
#include "graph/shader.h"

namespace dk::graph
{

shader::shader() noexcept
	: m_id(0)
{}

shader::~shader() noexcept /* override */
{
	this->destroy();
}

/* static */ GLenum shader::convert_to_gl_type(shader_type type) noexcept
{
	switch (type) {
		case shader_type::VERTEX:   return GL_VERTEX_SHADER;
		case shader_type::GEOMETRY: return GL_GEOMETRY_SHADER;
		case shader_type::FRAGMENT: return GL_FRAGMENT_SHADER;
	}

	DK_LOG_ERROR("Unsupported shader type");
	return 0;
}

status shader::create(string_view file_path, shader_type type) noexcept
{
	shader_data data;
	if (auto ret = data.create(file_path); !ret)
		return ret;

	return this->create(data, type);
}

status shader::create(const shader_data& data, shader_type type) noexcept
{
	m_id = GL_CALL(glCreateShader(convert_to_gl_type(type)));
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader");
		return status::ERROR;
	}

	auto src = data.data().data(); /* triple! */
	GLint len = data.data().size();
	GL_CALL(glShaderSource(m_id, 1, &src, &len));
	GL_CALL(glCompileShader(m_id));

	GLint val;
	GL_CALL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetShaderInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to compile shader '", data.file_path(), "':\n\t", string_view(buff, val));
		return status::ERROR;
	}

	DK_LOG_OK("Shader '", data.file_path(), "' created");
	return status::OK;
}

void shader::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteShader(m_id));
		m_id = 0;
	}
}

}
