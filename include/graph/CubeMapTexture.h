#ifndef __DK_GRAPH_CUBE_MAP_TEXTURE_H__
#define __DK_GRAPH_CUBE_MAP_TEXTURE_H__

#include <GL/gl.h>
#include "Status.h"
#include "graph/TextureData.h"
#include "containers/StringView.h"

namespace dk::graph
{

class CubeMapTexture final: public Resource
{
private:
	GLuint m_id;

public:
	CubeMapTexture() noexcept : CubeMapTexture(nullptr) {}
	CubeMapTexture(ResourceManager* res_mgr) noexcept;
	~CubeMapTexture() noexcept override;

	void enable() const noexcept;
	void disable() const noexcept;

	Status create(const TextureData& right, const TextureData& left, const TextureData& top,
		const TextureData& bottom, const TextureData& front, const TextureData& back) noexcept;
	Status create(StringView right, StringView left, StringView top,
		StringView bottom, StringView front, StringView back) noexcept;

	void destroy() noexcept;
};

}

#endif  //  !__DK_GRAPH_CUBE_MAP_TEXTURE_H__
