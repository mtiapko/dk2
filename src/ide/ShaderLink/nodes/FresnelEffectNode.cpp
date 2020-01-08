#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/ide/ShaderLink/Node.h"
#include "dk/Core.h"

namespace dk::ide::ShaderLink
{

class FresnelEffectNode final : public Node
{
private:
	static constexpr char ViewDir[] = "View Dir";
	static constexpr char Power[]   = "Power";
	static constexpr char Out[]     = "Out";

	static StringView FresnelEffect(Vec3<ViewDir>, Vec1<Power>, Vec1<Out>&) noexcept
	{
		return
			"{\n"
			"	Out = pow((1.0 - clamp(dot(normalize(norm), normalize(ViewDir)), 0.0, 1.0)), Power);\n"
			"}\n";
	}

	static inline const NodeClassEntry<FresnelEffectNode> s_class_entry { "Fresnel Effect", FresnelEffect };
};

}
