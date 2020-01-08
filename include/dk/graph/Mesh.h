#ifndef __DK_GRAPH_MESH_H__
#define __DK_GRAPH_MESH_H__

#include "dk/graph/MeshData.h"
#include "dk/sys/ResourceDataOwner.h"

namespace dk::graph
{

class Mesh : public Resource, public sys::ResourceDataOwner<MeshData>
{
public:
	DK_RESOURCE_TYPE_INFO(MESH);

	virtual void render() noexcept = 0;
};

}

#endif // !__DK_GRAPH_MESH_H__
