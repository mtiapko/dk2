#ifndef __DK_GRAPH_CAMERA_H__
#define __DK_GRAPH_CAMERA_H__

#include "math/Vec.h"
#include "math/Mat.h"

namespace dk::graph
{

class Camera
{
private:
	static constexpr float MOVE_SPEED = 0.05f;
	static constexpr float ROT_SPEED = 0.05f;

	math::Vec3f m_pos;
	math::Vec3f m_dir;
	math::Vec3f m_up;

public:
	Camera() noexcept;

	math::Mat4f view() const noexcept;

	void update() noexcept;
};

}

#endif  //  !__DK_GRAPH_CAMERA_H__
