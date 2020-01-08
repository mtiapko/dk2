#ifndef __DK_GRAPH_MODEL_H__
#define __DK_GRAPH_MODEL_H__

//#include "dk/graph/ModelData.h"
#include "dk/containers/Vector.h"
#include "dk/graph/SubModel.h"
#include "dk/Resource.h"

namespace dk::graph
{

class Model final : public Resource
{
private:
	Vector<SubModel> m_sub_models;

public:
	DK_RESOURCE_TYPE_INFO(MODEL);

	Vector<SubModel>& sub_models() noexcept { return m_sub_models; } // TODO: const
	SubModel& new_sub_model() noexcept { return m_sub_models.emplace_back(); }
};

}

#endif // !__DK_GRAPH_MODEL_H__
