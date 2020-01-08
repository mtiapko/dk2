#include <GL/glew.h>
#include "dk/Mem.h"
#include "Shader.h"
#include "Debug.h"

namespace gl
{

void Shader::enable() noexcept /* override */
{
	GL_CALL(glUseProgram(m_id));
}

void Shader::disable() noexcept /* override */
{
	GL_CALL(glUseProgram(0));
}

void Shader::set_arg(GLint id, int data) noexcept /* override */
{
	GL_CALL(glUniform1i(id, data));
}

void Shader::set_arg(GLint id, float data) noexcept /* override */
{
	GL_CALL(glUniform1f(id, data));
}

void Shader::set_arg(GLint id, const math::Vec2f& data) noexcept /* override */
{
	GL_CALL(glUniform2f(id, data.x, data.y));
}

void Shader::set_arg(GLint id, const math::Vec3f& data) noexcept /* override */
{
	GL_CALL(glUniform3f(id, data.x, data.y, data.z));
}

void Shader::set_arg(GLint id, const math::Vec4f& data) noexcept /* override */
{
	GL_CALL(glUniform4f(id, data.x, data.y, data.z, data.w));
}

void Shader::set_arg(GLint id, const math::Mat4f& data) noexcept /* override */
{
	GL_CALL(glUniformMatrix4fv(id, 1, GL_TRUE, data.data));
}

void Shader::set_arg(graph::ShaderParamID param_id, const graph::ShaderArg& arg) noexcept /* override */
{
	auto id = std::lower_bound(m_params.begin(), m_params.end(), param_id,
		[](const auto& param, auto param_id) noexcept { return (param.first < param_id); });
	if (id == m_params.end() || id->first != param_id) {
		// TODO: maybe remove and just print error message?
		const auto& param_name = get_param_name(param_id);
		if (param_name.empty() || !this->add_param(param_name, param_id))
			return;

		DK_LOG_WARNING("Automatically added new parameter '", param_name, "' to shader");
		return this->set_arg(param_id, arg); // TODO: no. too dirty. rewrite
	}

	switch (arg.type()) {
		case graph::ShaderArgType::INT:   return this->set_arg(id->second, arg.data().int_data);
		case graph::ShaderArgType::FLOAT: return this->set_arg(id->second, arg.data().float_data);
		case graph::ShaderArgType::VEC2:  return this->set_arg(id->second, arg.data().vec2_data);
		case graph::ShaderArgType::VEC3:  return this->set_arg(id->second, arg.data().vec3_data);
		case graph::ShaderArgType::VEC4:  return this->set_arg(id->second, arg.data().vec4_data);
		case graph::ShaderArgType::MAT4:  return this->set_arg(id->second, arg.data().mat4_data);
		default:
			DK_LOG_ERROR("gl::Shader::set_arg() does not implemented for type #", (int)arg.type());
	}
}

Status Shader::add_param(const String& name, graph::ShaderParamID param_id) noexcept /* override */
{
	GLint id = GL_CALL_RET(glGetUniformLocation(m_id, name.data()));
	if (id == -1) {
		// TODO: uncomment
		// DK_LOG_ERROR("Param '", name, "' does not exist in shader");
		return Status::ERROR;
	}

	m_params.insert(std::upper_bound(m_params.begin(), m_params.end(), param_id,
		[](auto param_id, const auto& param) noexcept { return (param_id < param.first); }),
		{ param_id, id });
	return Status::OK;
}

Status Shader::create() noexcept /* override */
{
	m_params.clear();
	m_id = GL_CALL(glCreateProgram());
	if (m_id == 0) {
		DK_LOG_ERROR("OpenGL failed to create shader");
		return Status::ERROR;
	}

	auto shader_data = (graph::ShaderData*)this->resource_data();
	for (const auto sub_shader: shader_data->sub_shaders)
		GL_CALL(glAttachShader(m_id, ((SubShader*)sub_shader)->id()));

	GLint val;
	GL_CALL(glLinkProgram(m_id));
	GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &val));
	if (val != GL_TRUE) {
		GL_CALL(glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &val));

		char buff[val];
		GL_CALL(glGetProgramInfoLog(m_id, val, nullptr, buff));
		DK_LOG_ERROR("OpenGL failed to link shader: ", StringView(buff, val));
		return Status::ERROR;
	}

	// XXX: is it good idea of implicite detaching?
	for (const auto sub_shader: shader_data->sub_shaders)
		GL_CALL(glDetachShader(m_id, ((SubShader*)sub_shader)->id()));

	return Status::OK;
}

void Shader::destroy() noexcept /* override */
{
	if (m_id != 0) {
		GL_CALL(glDeleteProgram(m_id));
		m_id = 0;
	}
}

}
