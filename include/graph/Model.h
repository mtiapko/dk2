#ifndef __DK_GRAPH_MODEL_H__
#define __DK_GRAPH_MODEL_H__

#include <GL/gl.h>
#include "Status.h"
#include "graph/Entity.h"
#include "graph/ModelData.h"

namespace dk::graph
{

class Model final: public Resource, public Entity
{
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_indx_count;

public:
	Model() noexcept : Model(nullptr) {}
	Model(ResourceManager* res_mgr) noexcept;
	~Model() noexcept override;

	static ResourceType type() noexcept { return ResourceType::MODEL; }

	void update() noexcept override;
	void render() noexcept override;

	Status create(const ModelData& data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_MODEL_H__
