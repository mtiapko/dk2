#ifndef __DK_ECS_COMPONENTS_ARRAY_H__
#define __DK_ECS_COMPONENTS_ARRAY_H__

#include "dk/containers/Array.h"
#include "dk/ecs/ComponentRef.h"

namespace dk::ecs
{

using ComponentsArray = Array<ComponentRef<Component>, Component::get_max_id()>;

}

#endif // !__DK_ECS_COMPONENTS_ARRAY_H__
