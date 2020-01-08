#include <GL/glew.h>
#include "dk/ImGui/Manager.h"
#include "Renderer.h"
#include "Debug.h"

namespace gl
{

void Renderer::clear() noexcept /* override */
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

Status Renderer::create() noexcept
{
	if (!m_is_created) {
		auto ret = glewInit();
		if (ret != GLEW_NO_ERROR) {
			DK_LOG_ERROR("Failed to initialize GLEW: ", glewGetString(ret),
				". Note: use 'glew-wayland' from AUR");
			//  return status::ERROR;  TODO: use glew-wayland
		}

		m_is_created = true;
		DK_LOG_OK("GLEW ", glewGetString(GLEW_VERSION), " initalized");

		// TODO: remove
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GL_CALL(glEnable(GL_DEPTH_TEST));
		GL_CALL(glClearColor(0.05f, 0.115f, 0.115f, 1.0f));
		DK_LOG_OK("Graphic renderer created");

		if (auto err = ImGui::Manager::create(); !err)
			return err;

		auto vert = Core::get().resource_manager().import<graph::SubShader>("res/shader/default_vert.glsl");
		if (vert == nullptr)
			return Status::ERROR;

		auto frag = Core::get().resource_manager().import<graph::SubShader>("res/shader/default_frag.glsl");
		if (frag == nullptr)
			return Status::ERROR;

		static graph::ShaderData data;
		data.sub_shaders.emplace_back(vert);
		data.sub_shaders.emplace_back(frag);
		if (auto err = m_default_shader.create_from_resource_data(&data); !err) {
			DK_LOG_ERROR("Failed to create default shader");
			return err;
		}

		// TODO: add?
		//m_default_shader.graph::Shader::add_param("view_proj");
		//m_default_shader.graph::Shader::add_param("DK_DIFFUSE_TEX");
		//m_default_shader.graph::Shader::add_param("DK_SPECULAR_TEX");
		//m_default_shader.graph::Shader::add_param("DK_NORMAL_TEX");
		//m_default_shader.graph::Shader::add_param("kek");
		//m_default_shader.graph::Shader::add_param("camera_pos");
	}

	return Status::OK;
}

}
