#ifndef __DK_GL_PLUGIN_H__
#define __DK_GL_PLUGIN_H__

#include "dk/Core.h"
#include "dk/Log.h"
#include "SubShaderImporter.h"
#include "TextureImporter.h"
#include "ModelImporter.h"
#include "Renderer.h"

using namespace dk;

namespace gl
{

class Plugin final : public sys::Plugin
{
private:
	Core*             m_core;
	SubShaderImporter m_sub_shader_importer;
	TextureImporter   m_tex_importer;
	ModelImporter     m_model_importer;
	Renderer          m_renderer;

public:
	StringView name() const noexcept override { return "gl"; }

	Status create() noexcept override
	{
		m_core = &Core::get();
		m_core->set_active<graph::Renderer>(&m_renderer);

		/* shaders */
		m_core->resource_manager().add_importer("glsl", ResourceType::SUB_SHADER_DATA, &m_sub_shader_importer);
		m_core->resource_manager().add_importer("glsl", ResourceType::SUB_SHADER,      &m_sub_shader_importer);

		/* textures */
		m_core->resource_manager().add_importer("tga",  ResourceType::TEXTURE_DATA, &m_tex_importer);
		m_core->resource_manager().add_importer("tga",  ResourceType::TEXTURE,      &m_tex_importer);
		m_core->resource_manager().add_importer("png",  ResourceType::TEXTURE_DATA, &m_tex_importer);
		m_core->resource_manager().add_importer("png",  ResourceType::TEXTURE,      &m_tex_importer);
		m_core->resource_manager().add_importer("jpg",  ResourceType::TEXTURE_DATA, &m_tex_importer);
		m_core->resource_manager().add_importer("jpg",  ResourceType::TEXTURE,      &m_tex_importer);
		m_core->resource_manager().add_importer("jpeg", ResourceType::TEXTURE_DATA, &m_tex_importer);
		m_core->resource_manager().add_importer("jpeg", ResourceType::TEXTURE,      &m_tex_importer);

		/* models */
		m_core->resource_manager().add_importer("obj",   ResourceType::MODEL, &m_model_importer);
		m_core->resource_manager().add_importer("fbx",   ResourceType::MODEL, &m_model_importer);
		m_core->resource_manager().add_importer("stp",   ResourceType::MODEL, &m_model_importer);
		m_core->resource_manager().add_importer("gltf",  ResourceType::MODEL, &m_model_importer);
		m_core->resource_manager().add_importer("blend", ResourceType::MODEL, &m_model_importer);

		return Status::OK;
	}

	void destroy() noexcept override
	{
		if (m_core->active<graph::Renderer>() == &m_renderer)
			m_core->set_active<graph::Renderer>(nullptr);
	}
};

}

#endif // !__DK_GL_PLUGIN_H__
