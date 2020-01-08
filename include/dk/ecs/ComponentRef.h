#ifndef __DK_ECS_COMPONENT_REF_H__
#define __DK_ECS_COMPONENT_REF_H__

#include "dk/ecs/ComponentManager.h"

namespace dk::ecs
{

template<typename ComponentT>
ComponentRef<ComponentT>::ComponentRef() noexcept
	: m_id(Component::get_null_id())
{
	ComponentManager<ComponentT>::add_component_ref(this);
}

template<typename ComponentT>
ComponentRef<ComponentT>::ComponentRef(ComponentT* ptr) noexcept
	: m_id((ComponentID)std::distance(ComponentManager<ComponentT>::get_components().data(), ptr))
{
	ComponentManager<ComponentT>::add_component_ref(this);
}

template<typename ComponentT>
ComponentRef<ComponentT>::operator ComponentT&() const noexcept
{
	return this->deref();
}

template<typename ComponentT>
ComponentT& ComponentRef<ComponentT>::deref() const noexcept
{
	return ComponentManager<ComponentT>::get_component(m_id);
}

template<typename ComponentT>
void ComponentRef<ComponentT>::reset_ref() noexcept
{
	ComponentManager<ComponentT>::remove_component_ref(this);
	m_id = Component::get_null_id();
}

}

#endif // !__DK_ECS_COMPONENT_REF_H__
