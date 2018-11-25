#include <GL/glew.h>
#include "assert.h"
#include "graphic/gl_call.h"
#include "graphic/shader_program.h"

namespace dk
{

void shader_program::enable() const
{
	GL_CALL(glUseProgram(m_shader_program));
}

void shader_program::disable() const
{
	GL_CALL(glUseProgram(0));
}

ret_code shader_program::add_shader(const shader& shader) const
{
	DK_ASSERT(m_shader_program != 0);
	GL_CALL(glAttachShader(m_shader_program, shader.get_native()));
	return ret_code::OK;
}

ret_code shader_program::create()
{
	m_shader_program = GL_CALL(glCreateProgram());
	return ret_code::OK;
}

ret_code shader_program::link()
{
	GLint is_linked;
	GL_CALL(glLinkProgram(m_shader_program));
	GL_CALL(glGetProgramiv(m_shader_program, GL_LINK_STATUS, &is_linked));
	if (is_linked != GL_TRUE) {
		GLint log_len;
		GL_CALL(glGetProgramiv(m_shader_program, GL_INFO_LOG_LENGTH, &log_len));

		char log[log_len];
		GL_CALL(glGetProgramInfoLog(m_shader_program, log_len, nullptr, log));
		DK_LOG_ERROR("Failed to link shader program:\n", (string_view)log);
		return ret_code::ERROR;
	}

	GLsizei count;
	std::array<GLuint, 8> shaders;
	while (true) {
		GL_CALL(glGetAttachedShaders(m_shader_program, shaders.size(), &count, shaders.data()));
		if (count == 0)
			break;

		for (GLsizei i = 0; i < count; ++i)
			GL_CALL(glDetachShader(m_shader_program, shaders[i]));
	}

	DK_LOG_OK("Shader program linked");
	return ret_code::OK;
}

}
