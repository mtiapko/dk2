#ifndef __DK_GRAPH_RENDER_QUEUE_H__
#define __DK_GRAPH_RENDER_QUEUE_H__

#include "dk/containers/Vector.h"
#include "dk/graph/QueuedRenderable.h"

namespace dk::graph
{

enum class RenderQueueType
{
	BACKGROUND  = 0,
	DEFAULT     = 1,
	TRANSPARENT = 2,
	OVERLAY     = 3,

	RENDER_QUEUE_TYPE_SIZE
};

class RenderQueue
{
private:
	Vector<QueuedRenderable> m_queued_renderables;

public:
	void sort() noexcept { std::sort(m_queued_renderables.begin(), m_queued_renderables.end()); }
	void clear() noexcept { m_queued_renderables.clear(); }

	void add(uint64_t hash, const ecs::RendererComponent* renderer) noexcept
	{
		m_queued_renderables.emplace_back(hash, renderer);
	}

	const Vector<QueuedRenderable>& queued_renderables() const noexcept
	{
		return m_queued_renderables;
	}
};

}

#endif // !__DK_GRAPH_RENDER_QUEUE_H__
