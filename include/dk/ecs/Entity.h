#ifndef __DK_ECS_ENTITY_H__
#define __DK_ECS_ENTITY_H__

#include "dk/ecs/ComponentsArray.h"

namespace dk::ecs
{

class Entity
{
private:
	ComponentsArray m_components;

public:
	template<typename ComponentT>
	bool has_component() const noexcept
	{
		return !m_components[Component::get_id<ComponentT>()].is_ref_null();
	}

	template<typename ComponentT, typename... Args>
	ComponentT* add_component(Args&&... args) noexcept
	{
		auto component = ComponentManager<ComponentT>::new_component(std::forward<Args>(args)...);
		(ComponentRef<ComponentT>&)m_components[Component::get_id<ComponentT>()] = component;
		return component;
	}

	template<typename ComponentT>
	ComponentT* get_component() noexcept
	{
		const auto id = Component::get_id<ComponentT>();
		auto& component_ref = (ComponentRef<ComponentT>&)m_components[id];

		DK_ASSERT(!component_ref.is_ref_null(), "Component #", id, " does not exist in this entity");
		return &component_ref.deref();
	}
};

}

#endif // !__DK_ECS_ENTITY_H__
