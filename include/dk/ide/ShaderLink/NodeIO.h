#ifndef __DK_IDE_SHADER_LINK_NODE_IO_H__
#define __DK_IDE_SHADER_LINK_NODE_IO_H__

#include "dk/containers/StringView.h"

namespace dk::ide::ShaderLink
{

enum class NodeIOType
{
	DYNAMIC = 0,

	/* vec */
	VEC1,
	VEC2,
	VEC3,
	VEC4,
	DYNAMIC_VEC,

	/* mat */
	MAT2,
	MAT3,
	MAT4,
	DYNAMIC_MAT,

	/* tex */
	TEX_2D
};

template<NodeIOType Type, const char Name[]>
struct Base
{
	static constexpr NodeIOType type = Type;
	static constexpr StringView name = Name;
};

template<const char Name[]> struct Dynamic : public Base<NodeIOType::DYNAMIC, Name> {};

/* vec */
template<const char Name[]> struct Vec1       : public Base<NodeIOType::VEC1,        Name> {};
template<const char Name[]> struct Vec2       : public Base<NodeIOType::VEC2,        Name> {};
template<const char Name[]> struct Vec3       : public Base<NodeIOType::VEC3,        Name> {};
template<const char Name[]> struct Vec4       : public Base<NodeIOType::VEC4,        Name> {};
template<const char Name[]> struct DynamicVec : public Base<NodeIOType::DYNAMIC_VEC, Name> {};

/* mat */
template<const char Name[]> struct Mat2       : public Base<NodeIOType::MAT2,        Name> {};
template<const char Name[]> struct Mat3       : public Base<NodeIOType::MAT3,        Name> {};
template<const char Name[]> struct Mat4       : public Base<NodeIOType::MAT4,        Name> {};
template<const char Name[]> struct DynamicMat : public Base<NodeIOType::DYNAMIC_MAT, Name> {};

/* color */
template<const char Name[]> struct Color : public Base<NodeIOType::VEC3, Name> {};

/* tex */
template<const char Name[]> struct Tex2D : public Base<NodeIOType::TEX_2D, Name> {};

struct NodeIO
{
	NodeIOType type;
	StringView name;

	static StringView get_type_name(NodeIOType type) noexcept;
	static StringView get_type_name_short(NodeIOType type) noexcept;
	static bool is_vec_type(NodeIOType type) noexcept;
	static bool is_mat_type(NodeIOType type) noexcept;
	static bool is_dynamic_type(NodeIOType type) noexcept;

	NodeIO() noexcept = default;
	NodeIO(NodeIOType type, StringView name) noexcept
		: type(type)
		, name(name)
	{}
};

}

#endif // !__DK_IDE_SHADER_LINK_NODE_IO_H__
