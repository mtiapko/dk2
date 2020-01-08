#ifndef __DK_GL_MESH_H__
#define __DK_GL_MESH_H__

#include <GL/gl.h>
#include "dk/graph/Mesh.h"
#include "Common.h"

namespace gl
{

class Mesh final : public graph::Mesh
{
private:
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ibo = 0;
	GLuint m_indx_count = 0;

public:
	Mesh(class Renderer* renderer) noexcept { this->set_resource_creator((sys::ResourceCreator*)renderer); }
	~Mesh() noexcept override { this->destroy(); }

	void render() noexcept override;

	Status create() noexcept override;
	void destroy() noexcept override;
};

}

#endif // !__DK_GL_MESH_H__
