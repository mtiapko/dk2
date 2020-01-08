#include "dk/ide/ShaderLink/NodeIO.h"
#include "dk/Assert.h"

namespace dk::ide::ShaderLink
{

/* static */ StringView NodeIO::get_type_name(NodeIOType type) noexcept
{
	switch (type) {
		case NodeIOType::VEC1:   return "float ";
		case NodeIOType::VEC2:   return "vec2 ";
		case NodeIOType::VEC3:   return "vec3 ";
		case NodeIOType::VEC4:   return "vec4 ";
		case NodeIOType::MAT2:   return "mat2 ";
		case NodeIOType::MAT3:   return "mat3 ";
		case NodeIOType::MAT4:   return "mat4 ";
		case NodeIOType::TEX_2D: return "sampler2D ";
		default: break;
	}

	DK_ASSERT(false, "Unsupported node IO type: #", (int)type);
	return {};
}

/* static */ StringView NodeIO::get_type_name_short(NodeIOType type) noexcept
{
	switch (type) {
		case NodeIOType::DYNAMIC:     return "*";

		/* vec */
		case NodeIOType::VEC1:        return "V1";
		case NodeIOType::VEC2:        return "V2";
		case NodeIOType::VEC3:        return "V3";
		case NodeIOType::VEC4:        return "V4";
		case NodeIOType::DYNAMIC_VEC: return "V*";

		/* mat */
		case NodeIOType::MAT2:        return "M2";
		case NodeIOType::MAT3:        return "M3";
		case NodeIOType::MAT4:        return "M4";
		case NodeIOType::DYNAMIC_MAT: return "M*";

		/* tex */
		case NodeIOType::TEX_2D:      return "2D";
	}

	DK_ASSERT(false, "Unsupported node IO type: #", (int)type);
}

/* static */ bool NodeIO::is_vec_type(NodeIOType type) noexcept
{
	return (type >= NodeIOType::VEC1 && type <= NodeIOType::DYNAMIC_VEC);
}

/* static */ bool NodeIO::is_mat_type(NodeIOType type) noexcept
{
	return (type >= NodeIOType::MAT2 && type <= NodeIOType::DYNAMIC_MAT);
}

/* static */ bool NodeIO::is_dynamic_type(NodeIOType type) noexcept
{
	return (
		type == NodeIOType::DYNAMIC     ||
		type == NodeIOType::DYNAMIC_VEC ||
		type == NodeIOType::DYNAMIC_MAT);
}

}
