#ifndef __DK_ECS_COMPONENT_REF_DECL_H__
#define __DK_ECS_COMPONENT_REF_DECL_H__

#include "dk/ecs/Component.h"

namespace dk::ecs
{

template<typename ComponentT>
class ComponentRef
{
private:
	ComponentID m_id;

public:
	ComponentRef() noexcept;
	ComponentRef(ComponentT* ptr) noexcept;
	//TODO: ??? explicit ComponentRef(ComponentID id) noexcept : ComponentRef(), m_id(id) {}
	//TODO: ??? explicit ComponentRef(ComponentRef&& that) noexcept : ComponentRef(), m_id(that.m_id) { that.reset(); }
	~ComponentRef() noexcept { this->reset_ref(); }

	operator ComponentT&() const noexcept;
	ComponentT& deref() const noexcept;

	bool is_ref_null() const noexcept { return (m_id == Component::get_null_id()); }
	void reset_ref() noexcept;
};

}

#endif // !__DK_ECS_COMPONENT_REF_DECL_H__
