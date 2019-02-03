#ifndef __DK_GRAPH_GUI_H__
#define __DK_GRAPH_GUI_H__

#include "graph/imgui/imgui.h"  //  TODO: remove
#include "sys/events/MouseMoveEvent.h"
#include "sys/events/MousePressEvent.h"
#include "sys/events/MouseReleaseEvent.h"
#include "sys/events/KeyPressEvent.h"
#include "sys/events/KeyReleaseEvent.h"

namespace dk::graph
{

class GUI : public
	sys::EventListener<sys::MouseMoveEvent>,
	sys::EventListener<sys::MousePressEvent>,
	sys::EventListener<sys::MouseReleaseEvent>,
	sys::EventListener<sys::KeyPressEvent>,
	sys::EventListener<sys::KeyReleaseEvent>
{
private:
	static GUI s_this;  //  TODO: remove. GUI must be one per window

	static int convert_mouse_btn(sys::MouseBtn btn) noexcept;

public:
	static void update() noexcept;
	static void render() noexcept;

	void handle(const sys::MouseMoveEvent& e) noexcept override;
	void handle(const sys::MousePressEvent& e) noexcept override;
	void handle(const sys::MouseReleaseEvent& e) noexcept override;

	void handle(const sys::KeyPressEvent& e) noexcept override;
	void handle(const sys::KeyReleaseEvent& e) noexcept override;

	//  TODO: get window ptr. not static
	static Status create() noexcept;
};

}

#endif  //  !__DK_GRAPH_H__
