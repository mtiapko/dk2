#ifndef __DK_GRAPH_ENTITY_H__
#define __DK_GRAPH_ENTITY_H__

namespace dk::graph
{

class Entity
{
public:
	virtual ~Entity() noexcept = default;

	virtual void update() noexcept = 0;
	virtual void render() noexcept = 0;
};

}

#endif  //  !__DK_GRAPH_ENTITY_H__
