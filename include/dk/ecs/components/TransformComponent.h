#ifndef __DK_ECS_COMPONENTS_TRANSFORM_COMPONENT_H__
#define __DK_ECS_COMPONENTS_TRANSFORM_COMPONENT_H__

#include "dk/math/Vec.h"

namespace dk::ecs
{

struct TransformComponent
{
	math::Vec3f position;
	math::Vec3f orientation;
};

}

#endif // !__DK_ECS_COMPONENTS_TRANSFORM_COMPONENT_H__
