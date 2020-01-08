#include "dk/ide/ShaderLink/NodeClass.h"
#include "dk/ide/ShaderLink/Node.h"
#include "dk/ide/ShaderLink/Pin.h"

namespace dk::ide::ShaderLink
{

bool Pin::is_input() const noexcept
{
	return (m_node_pin_id < m_node->node_class()->inputs_count());
}

}
