#ifndef __DK_IDE_SHADER_LINK_UNIQUE_INPUT_NODE_H__
#define __DK_IDE_SHADER_LINK_UNIQUE_INPUT_NODE_H__

#include "dk/ide/ShaderLink/InputNode.h"

namespace dk::ide::ShaderLink
{

class UniqueInputNode : public InputNode
{
private:
	void gen_pins_name(size_t node_id) noexcept override;
};

}

#endif // !__DK_IDE_SHADER_LINK_UNIQUE_INPUT_NODE_H__
