#include "dk/graph/Shader.h"
#include "dk/ide/ShaderLink/InputNode.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

void InputNode::gen_pins_name(size_t node_id) noexcept /* override */
{
	m_pins_name.clear();
	m_pins_param_id.clear();

	m_pins_name.reserve(m_pins.size());
	m_pins_param_id.reserve(m_pins.size());

	const String node_id_str = std::to_string(node_id);
	for (const auto& io: m_node_class->io()) {
		auto& pin_name = m_pins_name.emplace_back();
		pin_name.reserve(this->name().size()
			+ !io.name.empty() /* '_' */ + io.name.size()
			+ 1 /* '_' */ + node_id_str.size());

		pin_name = m_name;
		if (!io.name.empty()) {
			pin_name += '_';
			pin_name += Core::convert_name(io.name); // TODO: pre-convert
		}

		pin_name += '_';
		pin_name += node_id_str;

		m_pins_param_id.emplace_back(graph::Shader::get_param_id(pin_name));
	}
}

Status InputNode::gen_code() noexcept /* override */
{
	for (size_t node_pin_id = 0; node_pin_id < m_pins.size(); ++node_pin_id) {
		auto pin = m_pins[node_pin_id];
		if (NodeIO::is_dynamic_type(pin->type()))
			return Status::ERROR;

		if (!pin->is_connected())
			continue;

		m_code += "uniform ";
		m_code += NodeIO::get_type_name(pin->type());
		m_code += m_pins_name[node_pin_id];
		m_code += ";\n";
	}

	return Status::OK;
}

}
