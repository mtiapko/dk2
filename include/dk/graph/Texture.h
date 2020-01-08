#ifndef __DK_GRAPH_TEXTURE_H__
#define __DK_GRAPH_TEXTURE_H__

#include "dk/graph/TextureData.h"
#include "dk/sys/ResourceDataOwner.h"

namespace dk::graph
{

class Texture : public Resource, public sys::ResourceDataOwner<TextureData>
{
public:
	DK_RESOURCE_TYPE_INFO(TEXTURE);

	// TODO: rewrite texture unit activation
	virtual void enable(uint32_t tex_unit) noexcept = 0;
	virtual void disable() noexcept = 0;
};

}

#endif // !__DK_GRAPH_TEXTURE_H__
