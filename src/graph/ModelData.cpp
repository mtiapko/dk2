#include "graph/ModelData.h"

namespace dk::graph
{

ModelData::ModelData(ResourceManager* res_mgr) noexcept
	: Resource(res_mgr)
{}

ModelData::~ModelData() noexcept /* override */
{
	this->destroy();
}

void ModelData::destroy() noexcept
{
}

}
