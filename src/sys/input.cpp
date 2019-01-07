#include <string.h>
#include "sys/input.h"
#include "sys/keyboard.h"
#include "sys/event_manager.h"
#include "sys/events/key_press_event.h"
#include "sys/events/key_release_event.h"
#include "sys/events/mouse_move_event.h"
#include "sys/events/mouse_press_event.h"
#include "sys/events/mouse_release_event.h"
#include "graph/window.h"

#define KEY(x) ((x) + 8)

namespace dk::sys
{

namespace
{
	/* key codes lie in the inclusive range [8, 255] */
	keyboard_btn keyboard_btn_map[256];
}

/* static */ void input::update() noexcept
{
	XEvent event;
	int event_count;
	while ((event_count = XPending(graph::window::display()))) {
		do {
			XNextEvent(graph::window::display(), &event);
			switch (event.type) {
				case KeyPress: event_manager<key_press_event>::get().send(keyboard_btn_map[event.xkey.keycode]); break;
				case KeyRelease: event_manager<key_release_event>::get().send(keyboard_btn_map[event.xkey.keycode]); break;
				case MotionNotify: event_manager<mouse_move_event>::get().send(event.xmotion.x, event.xmotion.y); break;
				case ButtonPress: event_manager<mouse_press_event>::get().send((mouse_btn)event.xbutton.button); break;
				case ButtonRelease: event_manager<mouse_release_event>::get().send((mouse_btn)event.xbutton.button); break;
			}
		} while (--event_count);
	}
}

/* static */ status input::create() noexcept
{
	memset(keyboard_btn_map, (int)keyboard_btn::UNKNOWN, sizeof(keyboard_btn_map));

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
	return status::OK;
}

}
