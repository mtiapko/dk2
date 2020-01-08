#ifndef __DK_GRAPH_SUB_SHADER_H__
#define __DK_GRAPH_SUB_SHADER_H__

#include "dk/graph/SubShaderData.h"
#include "dk/sys/ResourceDataOwner.h"

namespace dk::graph
{

class SubShader: public Resource, public sys::ResourceDataOwner<SubShaderData>
{
public:
	DK_RESOURCE_TYPE_INFO(SUB_SHADER);
};

}

#endif // !__DK_GRAPH_SUB_SHADER_H__
