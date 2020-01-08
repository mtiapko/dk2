#ifndef __DK_ECS_COMPONENTS_PHYSICAL_COMPONENT_H__
#define __DK_ECS_COMPONENTS_PHYSICAL_COMPONENT_H__

#include "dk/math/Vec.h"

namespace dk::ecs
{

struct PhysicalComponent
{
	math::Vec3f movement;
	math::Vec3f rotation;
};

}

#endif // !__DK_ECS_COMPONENTS_PHYSICAL_COMPONENT_H__
