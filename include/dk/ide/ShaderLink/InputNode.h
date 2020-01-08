#ifndef __DK_IDE_SHADER_LINK_INPUT_NODE_H__
#define __DK_IDE_SHADER_LINK_INPUT_NODE_H__

#include "dk/graph/ShaderParamID.h"
#include "dk/ide/ShaderLink/Node.h"

namespace dk::ide::ShaderLink
{

class InputNode : public Node
{
protected:
	Vector<graph::ShaderParamID> m_pins_param_id;

	void gen_pins_name(size_t node_id) noexcept override;
	Status gen_code() noexcept override;

public:
	const auto& pins_param_id() const noexcept { return m_pins_param_id; }
};

}

#endif // !__DK_IDE_SHADER_LINK_INPUT_NODE_H__
