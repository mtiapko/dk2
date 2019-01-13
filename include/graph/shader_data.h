#ifndef __DK_GRAPH_SHADER_DATA_H__
#define __DK_GRAPH_SHADER_DATA_H__

#include "status.h"
#include "resource.h"
#include "containers/string.h"
#include "containers/string_view.h"

namespace dk::graph
{

class shader_data final: public resource
{
private:
	string      m_data;
	string_view m_file_path;

public:
	shader_data() noexcept = default;
	~shader_data() noexcept override = default;

	static resource_type type() noexcept { return resource_type::SHADER_DATA; }

	const string& data() const noexcept { return m_data; }
	string_view file_path() const noexcept { return m_file_path; }

	status create(string_view path) noexcept;
};

}

#endif  //  !__DK_GRAPH_SHADER_DATA_H__
