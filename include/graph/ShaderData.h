#ifndef __DK_GRAPH_SHADER_DATA_H__
#define __DK_GRAPH_SHADER_DATA_H__

#include "Status.h"
#include "Resource.h"
#include "containers/String.h"
#include "containers/StringView.h"

namespace dk::graph
{

class ShaderData final: public Resource
{
private:
	String     m_data;
	StringView m_file_path;

public:
	ShaderData() noexcept : ShaderData(nullptr) {}
	ShaderData(ResourceManager* res_mgr) noexcept;
	~ShaderData() noexcept override = default;

	static ResourceType type() noexcept { return ResourceType::SHADER_DATA; }

	const String& data() const noexcept { return m_data; }
	StringView file_path() const noexcept { return m_file_path; }

	Status create(StringView path) noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_DATA_H__
