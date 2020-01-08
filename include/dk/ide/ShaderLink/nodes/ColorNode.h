#ifndef __DK_IDE_SHADER_LINK_NODES_COLOR_NODE_H__
#define __DK_IDE_SHADER_LINK_NODES_COLOR_NODE_H__

#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/ide/ShaderLink/InputNode.h"
#include "dk/math/Vec.h"

namespace dk::ide::ShaderLink
{

class ColorNode final : public InputNode
{
private:
	static constexpr char RGB[]   = "RGB";
	static constexpr char Alpha[] = "Alpha";

	static StringView Color(Vec3<RGB>&, Vec1<Alpha>&) noexcept { return {}; }

	static inline const NodeClassEntry<ColorNode> s_class_entry { "Color", Color };

	math::Vec4f m_color { 0.0f, 0.0f, 0.0f, 1.0f };

public:
	void draw() noexcept override;
	void update_shader_args(const class Core* core) const noexcept override;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODES_COLOR_NODE_H__
