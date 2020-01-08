#ifndef __DK_IDE_SHADER_LINK_NODES_DEFAULT_OUTPUT_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_DEFAULT_OUTPUT_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/ide/ShaderLink/OutputNode.h"

namespace dk::ide::ShaderLink
{

class DefaultOutputNode final : public OutputNode
{
private:
	static constexpr char Color[]    = "Color";
	static constexpr char Alpha[]    = "Alpha";
	static constexpr char ColorOut[] = "ColorOut";

	static StringView DefaultOutput(Vec3<Color>, Vec1<Alpha>, Vec4<ColorOut>&) noexcept
	{
		return
			"{\n"
			"	float diff = max(dot(norm, light_dir), 0.175);\n"
			"	vec3 diffuse = diff * Color;\n"
			"	ColorOut = vec4(diffuse, Alpha);\n"
			"}";
	}

	static const NodeClassEntry<DefaultOutputNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_DEFAULT_OUTPUT_NODE_H__
