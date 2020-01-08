#ifndef __DK_IDE_SHADER_LINK_NODES_ADD_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_ADD_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"

namespace dk::ide::ShaderLink
{

class AddNode final : public Node
{
private:
	static constexpr char A[]   = "A";
	static constexpr char B[]   = "B";
	static constexpr char Out[] = "Out";

	static StringView Add(Dynamic<A>, Dynamic<B>, Dynamic<Out>&) noexcept
	{
		return "{ Out = A + B; }";
	}

	static const NodeClassEntry<AddNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_ADD_NODE_H__
