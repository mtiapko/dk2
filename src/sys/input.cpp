#include "log.h"
#include "sys/input.h"
#include "sys/keyboard.h"
#include "sys/event_manager.h"
#include "sys/events/key_press_event.h"
#include "sys/events/key_release_event.h"
#include "sys/events/mouse_move_event.h"
#include "sys/events/mouse_press_event.h"
#include "sys/events/mouse_release_event.h"
#include "sys/events/window_close_event.h"
#include "graph/window.h"

#define KEY(x) ((x) + 8)

namespace dk::sys
{

namespace  //  TODO: make this static member and include everything in input.h file?
{
	/* key codes lie in the inclusive range [8, 255] */
	keyboard_btn keyboard_btn_map[256];  //  TODO: make map for mouse buttons?

	auto& key_press_event_mgr     = event_manager<key_press_event>::get();
	auto& key_release_event_mgr   = event_manager<key_release_event>::get();
	auto& mouse_move_event_mgr    = event_manager<mouse_move_event>::get();
	auto& mouse_press_event_mgr   = event_manager<mouse_press_event>::get();
	auto& mouse_release_event_mgr = event_manager<mouse_release_event>::get();
	auto& window_close_event_mgr  = event_manager<window_close_event>::get();
}

/* static */ void input::update() noexcept
{
	XEvent event;
	int event_count;
	while ((event_count = XPending(graph::window::display()))) {
		do {
			XNextEvent(graph::window::display(), &event);
			switch (event.type) {
				case KeyPress:      key_press_event_mgr.send(keyboard_btn_map[event.xkey.keycode]); break;
				case KeyRelease:    key_release_event_mgr.send(keyboard_btn_map[event.xkey.keycode]); break;
				case MotionNotify:  mouse_move_event_mgr.send(event.xmotion.x, event.xmotion.y); break;
				case ButtonPress:   mouse_press_event_mgr.send((mouse_btn)event.xbutton.button); break;
				case ButtonRelease: mouse_release_event_mgr.send((mouse_btn)event.xbutton.button); break;
				case ClientMessage: window_close_event_mgr.send(); break;
			}
		} while (--event_count);
	}
}

/* static */ status input::create() noexcept
{
	static_assert((int)keyboard_btn::UNKNOWN == 0,
		"static variable equals to zero (.bss segment), fill with UNKNOWN manually");
	/* memset(keyboard_btn_map, (int)keyboard_btn::UNKNOWN, sizeof(keyboard_btn_map)); */

	keyboard_btn_map[KEY(1)]   = keyboard_btn::ESCAPE;
	keyboard_btn_map[KEY(15)]  = keyboard_btn::TAB;
	keyboard_btn_map[KEY(57)]  = keyboard_btn::SPACE;
	keyboard_btn_map[KEY(28)]  = keyboard_btn::ENTER;
	keyboard_btn_map[KEY(111)] = keyboard_btn::DELETE;
	keyboard_btn_map[KEY(103)] = keyboard_btn::UP_ARROW;
	keyboard_btn_map[KEY(108)] = keyboard_btn::DOWN_ARROW;
	keyboard_btn_map[KEY(105)] = keyboard_btn::LEFT_ARROW;
	keyboard_btn_map[KEY(106)] = keyboard_btn::RIGHT_ARROW;

	keyboard_btn_map[KEY(42)]  = keyboard_btn::L_SHIFT;
	keyboard_btn_map[KEY(54)]  = keyboard_btn::R_SHIFT;
	keyboard_btn_map[KEY(29)]  = keyboard_btn::L_CTRL;
	keyboard_btn_map[KEY(97)]  = keyboard_btn::R_CTRL;
	keyboard_btn_map[KEY(56)]  = keyboard_btn::L_ALT;
	keyboard_btn_map[KEY(100)] = keyboard_btn::R_ALT;

	DK_LOG_OK("Input system created");
	return status::OK;
}

}
