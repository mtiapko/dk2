#ifndef __DK_GRAPH_MATERIAL_H__
#define __DK_GRAPH_MATERIAL_H__

#include "dk/graph/Shader.h"
#include "dk/graph/Texture.h"

namespace dk::graph
{

class Material final : public Resource // TODO: remove?
{
private:
	Shader* m_shader = nullptr;
	Vector<Texture*> m_textures;
	HashTable<ShaderParamID, ShaderArg> m_shader_args; // TODO: add vector with args?

public:
	~Material() noexcept override { this->destroy(); }

	DK_RESOURCE_TYPE_INFO(MATERIAL);

	// TODO: rename to '.apply_args()'?
	void enable() const noexcept
	{
		for (uint32_t i = 0; i < m_textures.size(); ++i)
			m_textures[i]->enable(i);

		for (const auto& shader_arg: m_shader_args)
			m_shader->set_arg(shader_arg.first, shader_arg.second);
	}

	Shader* shader() const noexcept { return m_shader; }
	void set_shader(Shader* shader) noexcept { m_shader = shader; }

	template<typename T>
	void set_shader_arg(ShaderParamID param_id, const T& data) noexcept
	{
		m_shader_args.emplace(param_id, ShaderArg(data));
	}

	void set_shader_arg(ShaderParamID param_id, Texture* data) noexcept
	{
		m_shader_args.emplace(param_id, (int)m_textures.size());
		m_textures.emplace_back(data);
	}

	template<typename T>
	void set_shader_arg(const String& param_name, const T& data) noexcept
	{
		return this->set_shader_arg(Shader::get_param_id(param_name), data);
	}

	void destroy() noexcept override;
};

}

#endif // !__DK_GRAPH_MATERIAL_H__
