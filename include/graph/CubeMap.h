#ifndef __DK_GRAPH_CUBE_MAP_H__
#define __DK_GRAPH_CUBE_MAP_H__

#include "graph/CubeMapTexture.h"
#include "graph/RendererModule.h"

namespace dk::graph
{

class CubeMap final: public Resource, public RendererModule<RendererModuleID::CUBE_MAP>
{
private:
	static GLuint  s_vao;
	static GLuint  s_vbo;
	static GLfloat s_cube_map_vertices[];

	const CubeMapTexture* m_tex;

public:
	CubeMap() noexcept;
	~CubeMap() noexcept override;

	static Status init() noexcept;
	static Status deinit() noexcept;

	void render() const noexcept;

	Status create(const CubeMapTexture& tex) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_CUBE_MAP_H__
