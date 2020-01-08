#ifndef __DK_IDE_SHADER_LINK_NODES_FLOAT_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_FLOAT_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/ide/ShaderLink/InputNode.h"

namespace dk::ide::ShaderLink
{

class FloatNode final : public InputNode
{
private:
	static constexpr char Value[] = "";

	static StringView Float(Vec1<Value>&) noexcept { return {}; }

	static inline const NodeClassEntry<FloatNode> s_class_entry { "Float", Float };

	float m_float = 1.0f;

public:
	void draw() noexcept override;
	void update_shader_args(const class Core* core) const noexcept override;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_FLOAT_NODE_H__
