#ifndef __DK_IDE_SHADER_LINK_NODES_MUL_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_MUL_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"

namespace dk::ide::ShaderLink
{

class MulNode final : public Node
{
private:
	static constexpr char A[]   = "A";
	static constexpr char B[]   = "B";
	static constexpr char Out[] = "Out";

	static StringView Mul(Dynamic<A>, Dynamic<B>, Dynamic<Out>&) noexcept
	{
		return "{ Out = A * B; }";
	}

	static const NodeClassEntry<MulNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_MUL_NODE_H__
