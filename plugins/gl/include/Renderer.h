#ifndef __DK_GL_RENDERER_H__
#define __DK_GL_RENDERER_H__

#include "dk/graph/Renderer.h"
#include "dk/Mem.h"
#include "dk/Log.h"
#include "Window.h"
#include "SubShader.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

namespace gl
{

class Renderer final : public graph::Renderer
{
private:
	bool m_is_created = false;
	Vector<UniquePtr<Window>>    m_windows;
	Vector<UniquePtr<SubShader>> m_sub_shaders;
	Vector<UniquePtr<Shader>>    m_shaders;
	Vector<UniquePtr<Texture>>   m_textures;
	Vector<UniquePtr<Mesh>>      m_meshes;
	Shader                       m_default_shader { this };

	template<typename T>
	void delete_resource(Vector<T>& vec, Resource* res, StringView name)
	{
		size_t size = vec.size();
		std::erase_if(vec, [res](auto& inst) noexcept { return res == (Resource*)inst.get(); });

		if (size != vec.size()) DK_LOG_OK(name, " deleted");
		else DK_LOG_ERROR("Renderer does not contain deleted resource");
	}

public:
	void clear() noexcept override;

	graph::Shader* default_shader() noexcept override
	{
		return &m_default_shader;
	}

	Resource* new_resource(ResourceType type) noexcept override
	{
		switch (type) {
			case ResourceType::WINDOW: return (Resource*)m_windows.emplace_back(dk_mem_new(Window, this)).get();
			case ResourceType::SUB_SHADER: return (Resource*)m_sub_shaders.emplace_back(dk_mem_new(SubShader, this)).get();
			case ResourceType::SHADER: return (Resource*)m_shaders.emplace_back(dk_mem_new(Shader, this)).get();
			case ResourceType::TEXTURE: return (Resource*)m_textures.emplace_back(dk_mem_new(Texture, this)).get();
			case ResourceType::MESH: return (Resource*)m_meshes.emplace_back(dk_mem_new(Mesh, this)).get();
			default:
				DK_LOG_ERROR("Renderer couldn't create this resource type: ", ResourceTypeNames[(int)type]);
				return nullptr;
		}
	}

	void delete_resource(Resource* res) noexcept override
	{
		switch (res->resource_type()) {
			case ResourceType::WINDOW: return delete_resource(m_windows, res, "Window");
			case ResourceType::SUB_SHADER: return delete_resource(m_sub_shaders, res, "SubShader");
			case ResourceType::SHADER: return delete_resource(m_shaders, res, "Shader");
			case ResourceType::TEXTURE: return delete_resource(m_textures, res, "Texture");
			case ResourceType::MESH: return delete_resource(m_meshes, res, "Mesh");
			default:
				DK_LOG_ERROR("Renderer couldn't delete this resource type: ",
					ResourceTypeNames[(int)res->resource_type()]);
				return;
		}
	}

	Status create() noexcept;
};

}

#endif // !__DK_GL_RENDERER_H__
