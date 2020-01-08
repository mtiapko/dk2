#ifndef __DK_GRAPH_SHADER_PARAM_H__
#define __DK_GRAPH_SHADER_PARAM_H__

#include "dk/containers/StringView.h"
#include "dk/containers/String.h"

namespace dk::graph
{



#if 0
enum class ShaderParamType
{
	/* base types */
	INT,
	FLOAT,

	/* math types */
	VEC2,
	VEC3,
	VEC4,
	MAT4,

	/* texture types */
	TEX_2D
};

class ShaderParam
{
private:
	String          m_name;
	ShaderParamType m_type;

public:
	ShaderParam(StringView name, ShaderParamType type) noexcept
		: m_name(name)
		, m_type(type)
	{}

	ShaderParamType type() const noexcept { return m_type; }
	StringView name() const noexcept { return m_name; }
};
#endif

}

#endif // !__DK_GRAPH_SHADER_PARAM_H__
