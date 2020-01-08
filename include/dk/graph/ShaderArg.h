#ifndef __DK_GRAPH_SHADER_ARG_H__
#define __DK_GRAPH_SHADER_ARG_H__

#include "dk/math/Vec.h"
#include "dk/math/Mat.h"

namespace dk::graph
{

enum class ShaderArgType
{
	INT = 0,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT4,
	TEX
};

union ShaderArgData
{
	int         int_data;
	float       float_data;
	math::Vec2f vec2_data;
	math::Vec3f vec3_data;
	math::Vec4f vec4_data;
	math::Mat4f mat4_data;

	ShaderArgData() noexcept = default;
	ShaderArgData(const ShaderArgData& that) noexcept = default;

	ShaderArgData(int i) noexcept                   : int_data(i)     {}
	ShaderArgData(float f) noexcept                 : float_data(f)   {}
	ShaderArgData(const math::Vec2f& vec2) noexcept : vec2_data(vec2) {}
	ShaderArgData(const math::Vec3f& vec3) noexcept : vec3_data(vec3) {}
	ShaderArgData(const math::Vec4f& vec4) noexcept : vec4_data(vec4) {}
	ShaderArgData(const math::Mat4f& mat4) noexcept : mat4_data(mat4) {}
};

class ShaderArg
{
private:
	ShaderArgType m_type;
	ShaderArgData m_data;

	template<typename T>
	static constexpr ShaderArgType get_type() noexcept
	{
		if (std::is_same_v<T, int>)         return ShaderArgType::INT;
		if (std::is_same_v<T, float>)       return ShaderArgType::FLOAT;
		if (std::is_same_v<T, math::Vec2f>) return ShaderArgType::VEC2;
		if (std::is_same_v<T, math::Vec3f>) return ShaderArgType::VEC3;
		if (std::is_same_v<T, math::Vec4f>) return ShaderArgType::VEC4;
		if (std::is_same_v<T, math::Mat4f>) return ShaderArgType::MAT4;
	}

public:
	template<typename T>
	ShaderArg(const T& data) noexcept
		: m_type(get_type<std::remove_cvref_t<T>>())
		, m_data(data)
	{}

	ShaderArgType type() const noexcept { return m_type; }
	const ShaderArgData& data() const noexcept { return m_data; }
};

}

#endif // !__DK_GRAPH_SHADER_ARG_H__
