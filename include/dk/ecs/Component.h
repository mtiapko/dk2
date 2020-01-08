#ifndef __DK_ECS_COMPONENT_H__
#define __DK_ECS_COMPONENT_H__

#include <cstdint>

namespace dk::ecs
{

using ComponentID = uint32_t;

class Component
{
private:
	static constexpr ComponentID s_max_id = 32;

	static ComponentID get_unique_id() noexcept
	{
		static ComponentID counter;
		return counter++;
	}

public:
	static constexpr ComponentID get_max_id() noexcept { return s_max_id; }
	static constexpr ComponentID get_null_id() noexcept { return (ComponentID)-1; }

	template<typename> static ComponentID get_id() noexcept
	{
		static ComponentID id = get_unique_id();
		return id;
	}
};

}

#endif // !__DK_ECS_COMPONENT_H__
