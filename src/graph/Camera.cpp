#include "sys/Keyboard.h"
#include "graph/Camera.h"

#include "Log.h"

namespace dk::graph
{

Camera::Camera() noexcept
	: m_pos(0.0f, 0.0f, 30.0f)
	, m_dir(0.0f, 0.0f, -1.0f)
	, m_up(0.0f, 1.0f, 0.0f)
{}

math::Mat4f Camera::view() const noexcept
{
	return math::Mat4f::get_look_at(m_pos, m_pos + m_dir, m_up);
}

void Camera::update() noexcept
{
	bool is_changed = false;
	if (sys::Keyboard::state(sys::KeyboardBtn::A)) {
		m_pos -= m_dir.cross(m_up).normalize() * MOVE_SPEED;
		is_changed = true;
	}

	if (sys::Keyboard::state(sys::KeyboardBtn::D)) {
		m_pos += m_dir.cross(m_up).normalize() * MOVE_SPEED;
		is_changed = true;
	}

	if (sys::Keyboard::state(sys::KeyboardBtn::W)) {
		m_pos += m_dir * MOVE_SPEED;
		is_changed = true;
	}

	if (sys::Keyboard::state(sys::KeyboardBtn::S)) {
		m_pos -= m_dir * MOVE_SPEED;
		is_changed = true;
	}

	if (is_changed)
		DK_LOG(m_pos);
}

}
