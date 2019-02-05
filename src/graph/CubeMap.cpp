#include <GL/glew.h>
#include "Assert.h"
#include "graph/Debug.h"
#include "graph/CubeMap.h"

namespace dk::graph
{

/* static */ GLuint  CubeMap::s_vao;
/* static */ GLuint  CubeMap::s_vbo;
/* static */ GLfloat CubeMap::s_cube_map_vertices[] = {
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,

	/**/ -1.0f, -1.0f,  1.0f,
	/**/ -1.0f, -1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/ -1.0f, -1.0f,  1.0f,

	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,

	/**/ -1.0f, -1.0f,  1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f, -1.0f,  1.0f,
	/**/ -1.0f, -1.0f,  1.0f,

	/**/ -1.0f,  1.0f, -1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/ -1.0f,  1.0f, -1.0f,

	/**/ -1.0f, -1.0f, -1.0f,
	/**/ -1.0f, -1.0f,  1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/ -1.0f, -1.0f,  1.0f,
	/**/  1.0f, -1.0f,  1.0f
};

CubeMap::CubeMap(ResourceManager* res_mgr) noexcept
	: Resource(res_mgr)
	, m_tex(nullptr)
{}

CubeMap::~CubeMap() noexcept /* override */
{
	this->destroy();
}

/* static */ Status CubeMap::init() noexcept
{
	GL_CALL(glGenVertexArrays(1, &s_vao));
	GL_CALL(glBindVertexArray(s_vao));

	GL_CALL(glGenBuffers(1, &s_vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, s_vbo));

	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_cube_map_vertices), s_cube_map_vertices, GL_STATIC_DRAW));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GL_CALL(glEnableVertexAttribArray(0));

	GL_CALL(glBindVertexArray(0));
	return Status::OK;
}

/* static */ Status CubeMap::deinit() noexcept
{
	GL_CALL(glDeleteVertexArrays(1, &s_vao));
	GL_CALL(glDeleteBuffers(1, &s_vbo));
	return Status::OK;
}

void CubeMap::render() const noexcept
{
	DK_ASSERT(s_vao != 0, "CubeMap::init() required before CubeMap::render()");
	DK_ASSERT(m_tex != nullptr, "Cube map texture does not set");

	m_tex->enable();
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glBindVertexArray(s_vao));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CALL(glDepthFunc(GL_LESS));
}

Status CubeMap::create(const CubeMapTexture& tex) noexcept
{
	m_tex = &tex;
	return Status::OK;
}

void CubeMap::destroy() noexcept
{
	m_tex = nullptr;
}

}
