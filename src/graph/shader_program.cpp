#include <GL/glew.h>
#include "graph/debug.h"
#include "graph/shader_program.h"

namespace dk::graph
{

shader_program::~shader_program() noexcept /* override */
{
	this->destroy();
}

void shader_program::enable() const noexcept
{
	GL_CALL(glUseProgram(m_id));
}

void shader_program::disable() const noexcept
{
	GL_CALL(glUseProgram(0));
}

status shader_program::add(string_view file_path, shader_type type) const noexcept
{
	shader inst;
	if (auto ret = inst.create(file_path, type); !ret)
		return ret;

	return this->add(inst);
}

status shader_program::add(const shader& inst) const noexcept
{
	GL_CALL(glAttachShader(m_id, inst.id()));
	return status::OK;
}

status shader_program::remove_shaders() const noexcept
{
	GLint count;
	GL_CALL(glGetProgramiv(m_id, GL_ATTACHED_SHADERS, &count));
	if (count == 0)
		return status::OK;

	GLuint shader_ids[count];
	GL_CALL(glGetAttachedShaders(m_id, count, nullptr, shader_ids));
	while (--count)
		GL_CALL(glDetachShader(m_id, shader_ids[count]));

	return status::OK;
}

status shader_program::create() noexcept
{
	m_id = GL_CALL(glCreateProgram());
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader program");
		return status::ERROR;
	}

	return status::OK;
}

status shader_program::link() const noexcept
{
	GLint val;
	GL_CALL(glLinkProgram(m_id));
	GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetProgramInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to link shader program: ", string_view(buff, val));
		return status::ERROR;
	}

	this->remove_shaders();  //  XXX: is it good idea of implicite detaching?
	DK_LOG_OK("Shader program created and linked");
	return status::OK;
}

void shader_program::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteProgram(m_id));
		m_id = 0;
	}
}

}
