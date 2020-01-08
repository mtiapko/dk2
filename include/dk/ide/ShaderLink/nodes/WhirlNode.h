#ifndef __DK_IDE_SHADER_LINK_NODES_WHIRL_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_WHIRL_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"

namespace dk::ide::ShaderLink
{

class WhirlNode final : public Node
{
private:
	static constexpr char Angle[] = "Angle";
	static constexpr char Out[]   = "Out";

	static StringView Whirl(Vec1<Angle>, Vec1<Out>&) noexcept
	{
		// TODO: https://github.com/gilescoope/shader-graph-nodes
		return
			"{\n"
			"	const vec2 Widths = vec2(30.0, 30.0);\n"
			"	vec3 UV = world_space_pos.xzy;\n" // TODO
			"\n"
			"	float Width = Widths.x + Widths.y;\n"
			"	float r = length(UV);\n"
			"	float theta = 57.2958 * atan(UV.y, UV.x) - Angle * r;\n"
			"	Out = mod(mod((theta + 0.5*Width), Width) + Width, Width) - 0.5 * Width;\n"
			"	Out = abs(Out) - 0.5*Widths.x;\n"
			"	Out = clamp(-Out/fwidth(Out), 0.0, 1.0);\n"
			"}";
	}

	static const NodeClassEntry<WhirlNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_WHIRL_NODE_H__
