#ifndef __DK_GRAPH_SHADER_DATA_H__
#define __DK_GRAPH_SHADER_DATA_H__

#include "dk/containers/Vector.h"
#include "dk/graph/SubShader.h"

namespace dk::graph
{

struct ShaderData final : public Resource
{
	Vector<SubShader*> sub_shaders;

	DK_RESOURCE_TYPE_INFO(SHADER_DATA);
};

}

#endif // !__DK_GRAPH_SHADER_DATA_H__
