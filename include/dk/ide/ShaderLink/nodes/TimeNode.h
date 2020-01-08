#ifndef __DK_IDE_SHADER_LINK_NODES_TIME_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_TIME_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/ide/ShaderLink/InputNode.h"

namespace dk::ide::ShaderLink
{

class TimeNode final : public InputNode
{
private:
	static constexpr char Out[]     = "Out";
	static constexpr char Sin[]     = "Sin";
	static constexpr char Sin_x2[]  = "Sin x2";
	static constexpr char Sin_x10[] = "Sin x10";

	static StringView Time(Vec1<Out>&, Vec1<Sin>&, Vec1<Sin_x2>&, Vec1<Sin_x10>&) noexcept { return {}; }

	static inline const NodeClassEntry<TimeNode> s_class_entry { "Time", Time };

public:
	void update_shader_args(const class Core* core) const noexcept override;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_TIME_NODE_H__
