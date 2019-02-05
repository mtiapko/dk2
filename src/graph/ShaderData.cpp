#include "fs/File.h"
#include "graph/ShaderData.h"

namespace dk::graph
{

ShaderData::ShaderData(ResourceManager* res_mgr) noexcept
	: Resource(res_mgr)
{}

Status ShaderData::create(StringView file_path) noexcept
{
	m_file_path = file_path;
	return fs::File::read(file_path, m_data);
}

}
