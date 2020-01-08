#ifndef __DK_GRAPH_CAMERA_H__
#define __DK_GRAPH_CAMERA_H__

#include "dk/math/Vec.h"
#include "dk/math/Mat.h"
#include "dk/sys/Keyboard.h"
#include "dk/sys/Mouse.h"

namespace dk::graph
{

class Camera
{
private:
	/* view */
	math::Mat4f m_view;
	math::Vec3f m_pos;
	math::Vec3f m_dir;
	math::Vec3f m_right;
	math::Vec3f m_up;

	float m_yaw;
	float m_pitch;

	/* projection */
	math::Mat4f m_proj;
	float       m_FOV;
	float       m_ratio;
	float       m_near;
	float       m_far;

	/* view & projection */
	math::Mat4f m_view_proj;

public:
	Camera(float FOV, float ratio, float near, float far) noexcept
		/* view */
		: m_pos(0.0f, 0.0f, 0.0f)
		, m_dir(0.0f, 0.0f, -1.0f)
		, m_right(1.0f, 0.0f, 0.0f)
		, m_up(0.0f, 1.0f, 0.0f)
		, m_yaw(-90.0f)
		, m_pitch(0.0f)

		/* projection */
		, m_FOV(FOV)
		, m_ratio(ratio)
		, m_near(near)
		, m_far(far)
	{ update_proj_matrix(); }

	const math::Vec3f& position()         const noexcept { return m_pos;       }
	const math::Vec3f& direction()        const noexcept { return m_dir;       }
	const math::Mat4f& view_matrix()      const noexcept { return m_view;      }
	const math::Mat4f& proj_matrix()      const noexcept { return m_proj;      }
	const math::Mat4f& view_proj_matrix() const noexcept { return m_view_proj; }

	void update_view_matrix() noexcept { m_view = math::Mat4f::get_look_at(m_pos, m_pos + m_dir, m_up); }
	void update_proj_matrix() noexcept { m_proj = math::Mat4f::get_perspective(m_FOV, m_ratio, m_near, m_far); }
	void update_view_proj_matrix() noexcept { m_view_proj = m_proj * m_view; }

	void update() noexcept // TODO: rename
	{
		float MOVE_SPEED = 0.165f;
		const float ROT_SPEED = 0.115f;

		if (sys::Keyboard::caps_lock_state())
			MOVE_SPEED = 1.0f;

		if (sys::Keyboard::state(sys::KeyboardBtn::A))
			m_pos += m_right * MOVE_SPEED;

		if (sys::Keyboard::state(sys::KeyboardBtn::D))
			m_pos -= m_right * MOVE_SPEED;

		if (sys::Keyboard::state(sys::KeyboardBtn::W))
			m_pos -= m_dir * MOVE_SPEED;

		if (sys::Keyboard::state(sys::KeyboardBtn::S))
			m_pos += m_dir * MOVE_SPEED;

		if (sys::Keyboard::state(sys::KeyboardBtn::SPACE))
			m_pos -= m_up * MOVE_SPEED;

		if (sys::Keyboard::state(sys::KeyboardBtn::LEFT_SHIFT))
			m_pos += m_up * MOVE_SPEED;

		if (sys::Mouse::dx() != 0 || sys::Mouse::dy() != 0) {
			m_yaw += sys::Mouse::dx() * ROT_SPEED;
			m_pitch += sys::Mouse::dy() * ROT_SPEED;
			m_pitch = math::Algo::clamp(m_pitch, -89.0f, 89.0f);

			math::Vec3f dir(
				math::Algo::cos(math::Algo::to_rad(m_yaw)) * math::Algo::cos(math::Algo::to_rad(m_pitch)),
				-math::Algo::sin(math::Algo::to_rad(m_pitch)),
				math::Algo::sin(math::Algo::to_rad(m_yaw)) * math::Algo::cos(math::Algo::to_rad(m_pitch))
			);

			m_dir = dir.normalize();
			m_right = m_dir.cross(math::Vec3f(0.0f, 1.0f, 0.0f)).normalize();
			m_up = m_right.cross(m_dir).normalize();
		}
	}
};

}

#endif // !__DK_GRAPH_CAMERA_H__
