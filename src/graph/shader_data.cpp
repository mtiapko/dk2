#include "fs/file.h"
#include "graph/shader_data.h"

namespace dk::graph
{

status shader_data::create(string_view file_path) noexcept
{
	m_file_path = file_path;
	return fs::file::read(file_path, m_data);
}

}
