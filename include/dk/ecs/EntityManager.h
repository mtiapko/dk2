#ifndef __DK_ECS_ENTITY_MANAGER_H__
#define __DK_ECS_ENTITY_MANAGER_H__

#include "dk/containers/UniquePtr.h"
#include "dk/ecs/Entity.h"

namespace dk::ecs
{

class EntityManager
{
private:
	static inline Vector<UniquePtr<Entity>> s_entities;

public:
	static const Vector<UniquePtr<Entity>>& get_entities() noexcept { return s_entities; }

	// TODO: EntityT???
	template<typename EntityT = Entity, typename... Args>
	EntityT* new_entity(Args&&... args) noexcept
	{
		return s_entities.emplace_back(dk_mem_new(EntityT, std::forward<Args>(args)...));
	}
};

}

#endif // !__DK_ECS_ENTITY_MANAGER_H__
