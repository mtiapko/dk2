#ifndef __DK_GRAPH_QUEUED_RENDERABLE_H__
#define __DK_GRAPH_QUEUED_RENDERABLE_H__

#include <bit>
#include <cstdint>
#include "dk/ecs/components/RendererComponent.h"

namespace dk::graph
{


union QueuedRenderableHash
{
	static_assert(std::endian::native == std::endian::little, "Swap transparent and opaque");
	uint64_t value;

	struct
	{
		uint32_t shader_hash;
		union
		{
			float    float_depth;
			uint32_t int_depth;
		};
	} transparent;

	struct
	{
		union
		{
			float    float_depth;
			uint32_t int_depth;
		};
		uint32_t shader_hash;
	} opaque;
};

class QueuedRenderable
{
private:
	uint64_t m_hash;
	const ecs::RendererComponent* m_renderer;

public:
	QueuedRenderable(uint64_t hash, const ecs::RendererComponent* renderer) noexcept
		: m_hash(hash)
		, m_renderer(renderer)
	{}

	bool operator<(const QueuedRenderable& that) const noexcept
	{
		return this->m_hash < that.m_hash;
	}

	const ecs::RendererComponent* renderer() const noexcept { return m_renderer; }
};

}

#endif // !__DK_GRAPH_QUEUED_RENDERABLE_H__
