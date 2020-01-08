#ifndef __DK_IM_GUI_MANAGER_H__
#define __DK_IM_GUI_MANAGER_H__

#include "dk/ImGui/imgui.h" // TODO: remove
#include "dk/ImGui/TextEditor.h"
#undef ImGui

#include "dk/sys/events/MouseMoveEvent.h"
#include "dk/sys/events/MousePressEvent.h"
#include "dk/sys/events/MouseReleaseEvent.h"
#include "dk/sys/events/KeyPressEvent.h"
#include "dk/sys/events/KeyReleaseEvent.h"

namespace dk
{

namespace ImGui
{

class Manager : public // TODO: check if public for all
	sys::EventListener<sys::MouseMoveEvent>,
	sys::EventListener<sys::MousePressEvent>,
	sys::EventListener<sys::KeyPressEvent>,
	sys::EventListener<sys::KeyReleaseEvent>
{
private:
	static Manager s_this; // TODO: remove. ImGUI must be one per window

	static int convert_mouse_btn(sys::MouseBtn btn) noexcept;

public:
	void handle(const sys::MouseMoveEvent& e) noexcept override;
	void handle(const sys::MousePressEvent& e) noexcept override;

	void handle(const sys::KeyPressEvent& e) noexcept override;
	void handle(const sys::KeyReleaseEvent& e) noexcept override;

	static void update() noexcept;
	static void render() noexcept;

	//  TODO: get window ptr. not static
	static Status create() noexcept;
	// TODO: destroy
};

}

}

#endif // !__DK_IM_GUI_MANAGER_H__
