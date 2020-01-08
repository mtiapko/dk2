#ifndef __DK_GRAPH_SUB_SHADER_DATA_H__
#define __DK_GRAPH_SUB_SHADER_DATA_H__

#include "dk/containers/StringView.h"
#include "dk/containers/String.h"
#include "dk/Resource.h"
#include "dk/Status.h"

namespace dk::graph
{

enum class SubShaderType
{
	VERTEX = 0,
	FRAGMENT
};

struct SubShaderData final : public Resource
{
	String        file_path;
	String        source;
	SubShaderType type;

	DK_RESOURCE_TYPE_INFO(SUB_SHADER_DATA);
};

}

#endif // !__DK_GRAPH_SUB_SHADER_DATA_H__
