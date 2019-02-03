#include "sys/Mouse.h"
#include "sys/Keyboard.h"
#include "graph/Camera.h"

#include "Log.h"

namespace dk::graph
{

Camera::Camera() noexcept
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_dir(0.0f, 0.0f, -1.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_yaw(-90.0f)
	, m_pitch(0.0f)
{
	//  TODO: think about static constexpr
	m_right = m_dir.cross(math::Vec3f(0.0f, 1.0f, 0.0f)).normalize();
}

math::Mat4f Camera::view() const noexcept
{
	return math::Mat4f::get_look_at(m_pos, m_pos + m_dir, m_up);
}

void Camera::update() noexcept
{
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

	//  TODO: subscribe to mouse move events
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

}
