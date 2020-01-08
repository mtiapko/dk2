#ifndef __DK_GRAPH_SUB_MODEL_H__
#define __DK_GRAPH_SUB_MODEL_H__

#include "dk/graph/Material.h"
#include "dk/graph/Mesh.h"

namespace dk::graph
{

class SubModel final : public Resource
{
private:
	Material m_material;
	Mesh*    m_mesh;

public:
	DK_RESOURCE_TYPE_INFO(SUB_MODEL);

	Material& material() noexcept { return m_material; }
	const Material& material() const noexcept { return m_material; }

	Mesh* mesh() const noexcept { return m_mesh; }
	void set_mesh(Mesh* mesh) noexcept { m_mesh = mesh; }
};

}

#endif // !__DK_GRAPH_SUB_MODEL_H__
