#ifndef __DK_ECS_COMPONENTS_RENDERER_COMPONENT_H__
#define __DK_ECS_COMPONENTS_RENDERER_COMPONENT_H__

#include "dk/graph/Model.h"
#include "dk/ecs/components/TransformComponent.h"
#include "dk/ecs/Entity.h"

namespace dk::ecs
{

struct RendererComponent
{
	ComponentRef<TransformComponent> transform;
	graph::Mesh*                     mesh; // TODO: const
	graph::Material*                 material; // TODO: const?

	RendererComponent(Entity* entity, graph::Mesh* mesh, graph::Material* material)
		: transform(entity->get_component<TransformComponent>())
		, mesh(mesh)
		, material(material)
	{}
};

}

#endif // !__DK_ECS_COMPONENTS_RENDERER_COMPONENT_H__
