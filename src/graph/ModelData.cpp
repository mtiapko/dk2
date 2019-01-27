#include "graph/ModelData.h"

namespace dk::graph
{

ModelData::~ModelData() noexcept /* override */
{
	this->destroy();
}

void ModelData::destroy() noexcept
{
}

}
