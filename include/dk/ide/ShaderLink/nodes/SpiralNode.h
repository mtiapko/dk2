#ifndef __DK_IDE_SHADER_LINK_NODES_SPIRAL_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_SPIRAL_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"

namespace dk::ide::ShaderLink
{

class SpiralNode final : public Node
{
private:
	static constexpr char Out[] = "Out";

	static StringView Spiral(Vec1<Out>&) noexcept
	{
		// TODO: https://github.com/gilescoope/shader-graph-nodes
		return
			"{\n"
			"	const vec2 Widths = vec2(5.0, 5.0);\n"
			"	vec3 UV = world_space_pos.xzy;\n" // TODO
			"\n"
			"	float Width = Widths.x + Widths.y;\n"
			"	float r = length(UV);\n"
			"	float theta = atan(UV.y, UV.x);\n"
			"	float k = (r/(Width/6.28318530718) - theta)/6.28318530718;\n"
			"	Out = abs(r - ((Width/6.28318530718)*(theta + 6.28318530718*round(k)))) - 0.5*Widths.x;\n"
			"	Out = clamp(-Out/fwidth(Out), 0.0, 1.0);\n"
			"}";
	}

	static const NodeClassEntry<SpiralNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_SPIRAL_NODE_H__
