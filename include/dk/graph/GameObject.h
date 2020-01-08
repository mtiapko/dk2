#ifndef __DK_GRAPH_GAME_OBJECT_H__
#define __DK_GRAPH_GAME_OBJECT_H__

#include "dk/ecs/Entity.h"
#include "dk/ecs/components/TransformComponent.h"

namespace dk::graph
{

class GameObject : public ecs::Entity
{
public:
	GameObject() noexcept
	{
		this->add_component<ecs::TransformComponent>();
	}
};

}

#endif // !__DK_GRAPH_GAME_OBJECT_H__
