#include <GL/glew.h>
#include "graph/Debug.h"
#include "graph/ShaderProgram.h"

namespace dk::graph
{

ShaderProgram::ShaderProgram() noexcept
	: m_id(0)
{}

ShaderProgram::~ShaderProgram() noexcept /* override */
{
	this->destroy();
}

void ShaderProgram::enable() const noexcept
{
	GL_CALL(glUseProgram(m_id));
}

void ShaderProgram::disable() const noexcept
{
	GL_CALL(glUseProgram(0));
}

Status ShaderProgram::uniform_location(StringView name, UniformLocation& location) const noexcept
{
	location = GL_CALL(glGetUniformLocation(m_id, name.data()));
	if (location == -1)
		DK_LOG_WARNING("Uniform variable with name '", name, "' does not exist");

	return Status::OK;
}

Status ShaderProgram::set_uniform(UniformLocation location, const math::Mat4f& val) const noexcept
{
	GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, val.data));
	return Status::OK;
}

Status ShaderProgram::set_uniform(UniformLocation location, float val) const noexcept
{
	GL_CALL(glUniform1f(location, val));
	return Status::OK;
}

Status ShaderProgram::add(StringView file_path, ShaderType type) const noexcept
{
	Shader shader;
	if (auto ret = shader.create(file_path, type); !ret)
		return ret;

	return this->add(shader);
}

Status ShaderProgram::add(const Shader& inst) const noexcept
{
	GL_CALL(glAttachShader(m_id, inst.id()));
	return Status::OK;
}

Status ShaderProgram::remove_shaders() const noexcept
{
	GLint count;
	GL_CALL(glGetProgramiv(m_id, GL_ATTACHED_SHADERS, &count));
	if (count == 0)
		return Status::OK;

	GLuint shader_ids[count];
	GL_CALL(glGetAttachedShaders(m_id, count, nullptr, shader_ids));
	while (--count)
		GL_CALL(glDetachShader(m_id, shader_ids[count]));

	return Status::OK;
}

Status ShaderProgram::create() noexcept
{
	m_id = GL_CALL(glCreateProgram());
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader program");
		return Status::ERROR;
	}

	return Status::OK;
}

Status ShaderProgram::link() const noexcept
{
	GLint val;
	GL_CALL(glLinkProgram(m_id));
	GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetProgramInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to link shader program: ", StringView(buff, val));
		return Status::ERROR;
	}

	this->remove_shaders();  //  XXX: is it good idea of implicite detaching?
	DK_LOG_OK("Shader program created and linked");
	return Status::OK;
}

void ShaderProgram::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteProgram(m_id));
		m_id = 0;
	}
}

}
