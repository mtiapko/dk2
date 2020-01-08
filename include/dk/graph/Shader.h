#ifndef __DK_GRAPH_SHADER_H__
#define __DK_GRAPH_SHADER_H__

#include "dk/containers/HashTable.h"
#include "dk/graph/ShaderParamID.h"
#include "dk/graph/ShaderData.h"
#include "dk/graph/ShaderArg.h"
#include "dk/sys/ResourceDataOwner.h"

namespace dk::graph
{

class Shader : public Resource, public sys::ResourceDataOwner<ShaderData>
{
protected: // TODO: private: and getter for name by id
	static inline HashTable<String, ShaderParamID> s_shader_param_IDs;

public:
	DK_RESOURCE_TYPE_INFO(SHADER);

	/* XXX: 'const String&' to avoid type casting '.find(String(name))' */
	static ShaderParamID get_param_id(const String& name) noexcept
	{
		auto shader_param_id = s_shader_param_IDs.find(name);
		if (shader_param_id != s_shader_param_IDs.end())
			return shader_param_id->second;

		auto [it, is_inserted] = s_shader_param_IDs.emplace(name, s_shader_param_IDs.size());
		return it->second;
	}

	static const String& get_param_name(ShaderParamID param_id) noexcept
	{
		auto it = std::find_if(s_shader_param_IDs.begin(), s_shader_param_IDs.end(),
			[param_id](const auto& pair) noexcept { return (param_id == pair.second); });

		if (it != s_shader_param_IDs.end())
			return it->first;

		/* XXX: empty string */
		static const String unknown_name {};
		return unknown_name;
	}

	virtual void enable() noexcept = 0;
	virtual void disable() noexcept = 0;

	// TODO: make protected?
	virtual void set_arg(ShaderParamID param_id, const ShaderArg& arg) noexcept = 0;

	// TODO: remove
	template<typename T>
	void set_arg(const String& name, const T& data) noexcept
	{
		this->set_arg(get_param_id(name), data);
	}

	virtual Status add_param(const String& name, ShaderParamID param_id) noexcept = 0;
	Status add_param(const String& name) noexcept
	{
		return this->add_param(name, get_param_id(name));
	}
};

}

#endif // !__DK_GRAPH_SHADER_H__
