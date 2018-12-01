#include "log.h"
#include "graphic/gl.h"
#include "graphic/shader.h"

namespace dk
{

GLenum shader::convert_type(shader_type type)
{
	switch (type) {
		case shader_type::VERTEX_SHADER: return GL_VERTEX_SHADER;
		case shader_type::FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
		case shader_type::GEOMETRY_SHADER: return GL_GEOMETRY_SHADER;
		default:
			DK_LOG_ERROR("Unsupported shader type");
			return 0;
	}
}

status shader::create(shader_type type, string_view src)
{
	m_shader = GL_CALL(glCreateShader(convert_type(type)));

	const GLchar* src_data = src.data();
	const GLint src_len = src.length();
	GL_CALL(glShaderSource(m_shader, 1, &src_data, &src_len));
	GL_CALL(glCompileShader(m_shader));

	GLint is_compiled;
	GL_CALL(glGetShaderiv(m_shader, GL_COMPILE_STATUS, &is_compiled));
	if (is_compiled != GL_TRUE) {
		GLint log_len;
		GL_CALL(glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &log_len));

		char log[log_len];
		GL_CALL(glGetShaderInfoLog(m_shader, log_len, nullptr, log));
		DK_LOG_ERROR("Failed to compile shader:\n", (string_view)log);
		return status::ERROR;
	}

	DK_LOG_OK("Shader compiled");
	return status::OK;
}

}
