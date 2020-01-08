#ifndef __DK_GRAPH_MODEL_DATA_H__
#define __DK_GRAPH_MODEL_DATA_H__

#include "dk/graph/Mesh.h"

namespace dk::graph
{

struct ModelData final : public Resource
{
public:
	Vector<MeshData*>    meshes;
	//Vector<TextureData*> textures;

public:
	DK_RESOURCE_TYPE_INFO(MODEL_DATA);

	void destroy() noexcept override {} // TODO
};

}

#endif // !__DK_GRAPH_MODEL_DATA_H__
