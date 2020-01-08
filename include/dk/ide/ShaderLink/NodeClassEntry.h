#ifndef __DK_IDE_SHADER_LINK_NODE_CLASS_ENTRY_H__
#define __DK_IDE_SHADER_LINK_NODE_CLASS_ENTRY_H__

#include "dk/ide/ShaderLink/NodeClass.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

/* forward declaration for 'std::is_base_of' */
class InputNode;
class UniqueInputNode;
class OutputNode;

template<typename NodeT>
class NodeClassEntry final : public NodeClass
{
public:
	template<typename... IO>
	NodeClassEntry(StringView name, StringView (*get_body_code)(IO...) noexcept) noexcept
		: NodeClass(name, get_body_code)
	{
		Core::add_node_class(this);
	}

	class Node* new_node() const noexcept override
	{
		return dk_mem_new(NodeT);
	}

	bool is_input_node() const noexcept override
	{
		return std::is_base_of_v<InputNode, NodeT>;
	}

	bool is_unique_input_node() const noexcept override
	{
		return std::is_base_of_v<UniqueInputNode, NodeT>;
	}

	bool is_output_node() const noexcept override
	{
		return std::is_base_of_v<OutputNode, NodeT>;
	}
};

}

#endif // !__DK_IDE_SHADER_LINK_NODE_CLASS_ENTRY_H__
