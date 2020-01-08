#ifndef __DK_GRAPH_MESH_DATA_H__
#define __DK_GRAPH_MESH_DATA_H__

#include "dk/math/Vec.h"
#include "dk/Resource.h"

namespace dk::graph
{

struct MeshDataVertex
{
	math::Vec3f position;
	math::Vec3f normal;
	math::Vec2f uv;
	math::Vec3f tangent;
	math::Vec3f bitangent;
};

struct MeshData final : public Resource
{
	Vector<MeshDataVertex> vertices;
	Vector<uint32_t>       indices;

	DK_RESOURCE_TYPE_INFO(MESH_DATA);
};

}

#endif // !__DK_GRAPH_MESH_DATA_H__
