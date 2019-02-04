#ifndef __DK_GRAPH_CUBE_MAP_H__
#define __DK_GRAPH_CUBE_MAP_H__

#include <GL/gl.h>
#include "Status.h"
#include "graph/TextureData.h"
#include "containers/StringView.h"

namespace dk::graph
{

class CubeMap final: public Resource
{
private:
	static GLuint  s_vao;
	static GLuint  s_vbo;
	static GLfloat s_cube_map_vertices[];

	GLuint m_id;

public:
	CubeMap() noexcept;
	~CubeMap() noexcept override;

	static Status init() noexcept;

	void render() const noexcept;

	Status create(const TextureData& right, const TextureData& left, const TextureData& top,
		const TextureData& bottom, const TextureData& front, const TextureData& back) noexcept;
	Status create(StringView right, StringView left, StringView top,
		StringView bottom, StringView front, StringView back) noexcept;

	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_CUBE_MAP_H__
