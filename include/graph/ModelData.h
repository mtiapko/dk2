#ifndef __DK_GRAPH_MODEL_DATA_H__
#define __DK_GRAPH_MODEL_DATA_H__

#include <stdint.h>
#include "math/Vec.h"
#include "Resource.h"
#include "containers/Vector.h"

namespace dk::graph
{

struct ModelDataVertex
{
	math::Vec3f pos;
	math::Vec3f norm;
	math::Vec2f uv;

	ModelDataVertex(math::Vec3f pos, math::Vec3f norm, math::Vec2f uv)
		: pos(pos)
		, norm(norm)
		, uv(uv)
	{}
};

struct ModelData final: public Resource
{
public:
	Vector<ModelDataVertex> vert;
	Vector<uint32_t>        indx;

	ModelData() noexcept : ModelData(nullptr) {}
	ModelData(ResourceManager* res_mgr) noexcept;
	~ModelData() noexcept override;

	static ResourceType type() noexcept { return ResourceType::MODEL_DATA; }

	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_MODEL_DATA_H__
