#ifndef __DK_ECS_COMPONENT_MANAGER_H__
#define __DK_ECS_COMPONENT_MANAGER_H__

#include "dk/containers/Vector.h"
#include "dk/ecs/ComponentRefDecl.h"

namespace dk::ecs
{

template<typename ComponentT>
class ComponentManager
{
private:
	static inline Vector<ComponentT> m_components;
	static inline Vector<ComponentRef<ComponentT>*> m_components_ref;

public:
	static Vector<ComponentT>& get_components() noexcept { return m_components; }
	static ComponentT& get_component(ComponentID id) noexcept { return m_components[id]; }

	static void add_component_ref(ComponentRef<ComponentT>* ref) noexcept { m_components_ref.emplace_back(ref); }
	static void remove_component_ref(const ComponentRef<ComponentT>* ref) noexcept
	{
		std::erase(m_components_ref, ref);
	}

	template<typename... Args>
	static ComponentT* new_component(Args&&... args) noexcept
	{
		return &m_components.emplace_back(std::forward<Args>(args)...);
	}
};

}

#endif // !__DK_ECS_COMPONENT_MANAGER_H__
