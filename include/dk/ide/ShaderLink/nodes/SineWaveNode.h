#ifndef __DK_IDE_SHADER_LINK_NODES_SINE_WAVE_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_SINE_WAVE_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"

namespace dk::ide::ShaderLink
{

class SineWaveNode final : public Node
{
private:
	static constexpr char Wavelength[] = "Wavelength";
	static constexpr char Amplitude[]  = "Amplitude";
	static constexpr char Out[]        = "Out";

	static StringView SineWave(Vec1<Wavelength>, Vec1<Amplitude>, Vec1<Out>&) noexcept
	{
		// TODO: https://github.com/gilescoope/shader-graph-nodes
		return
			"{\n"
			"	const vec2 Widths = vec2(0.1, 0.1);\n"
			"	vec2 UV = world_space_pos.xz;\n" // TODO
			"\n"
			"	float Width = Widths.x + Widths.y;\n"
			"	float y = 0.5*Amplitude * sin(6.28318530718 * UV.x/Wavelength);\n"
			"	Out = mod(mod((UV.y - y) , Width) + Width, Width);\n"
			"	Out = abs(Out - 0.5*Width) - 0.5* Widths.y;\n"
			"	Out = clamp(Out/fwidth(Out), 0.0, 1.0);\n"
			"}";
	}

	static const NodeClassEntry<SineWaveNode> s_class_entry;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_SINE_WAVE_NODE_H__
