#include "dk/ide/ShaderLink/UniqueInputNode.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

void UniqueInputNode::gen_pins_name(size_t /* node_id */) noexcept /* override */
{
	m_pins_name.clear();
	m_pins_param_id.clear();

	m_pins_name.reserve(m_pins.size());
	m_pins_param_id.reserve(m_pins.size());

	for (const auto& io: m_node_class->io()) {
		auto& pin_name = m_pins_name.emplace_back();
		pin_name.reserve(this->name().size()
			+ !io.name.empty() /* '_' */ + io.name.size());

		pin_name = m_name;
		if (!io.name.empty()) {
			pin_name += '_';
			pin_name += Core::convert_name(io.name); // TODO: pre-convert
		}

		m_pins_param_id.emplace_back(graph::Shader::get_param_id(pin_name));
	}
}

}
