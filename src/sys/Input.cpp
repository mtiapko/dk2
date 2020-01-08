#include "dk/sys/events/MouseReleaseEvent.h"
#include "dk/sys/events/WindowCloseEvent.h"
#include "dk/sys/events/KeyReleaseEvent.h"
#include "dk/sys/events/MousePressEvent.h"
#include "dk/sys/events/MouseMoveEvent.h"
#include "dk/sys/events/KeyPressEvent.h"
#include "dk/sys/EventManager.h"
#include "dk/sys/Keyboard.h"
#include "dk/sys/Input.h"
#include "dk/os/Descriptor.h"
#include "dk/Log.h"

#define KEY(x) ((x) + 8)

namespace dk::sys
{

namespace  //  TODO: make this static member and include everything in input.h file?
{
	/* key codes lie in the inclusive range [8, 255] */
	KeyboardBtn keyboard_btn_map[256];  //  TODO: make map for mouse buttons?

	auto& key_press_event_mgr     = EventManager<KeyPressEvent>::get();
	auto& key_release_event_mgr   = EventManager<KeyReleaseEvent>::get();
	auto& mouse_move_event_mgr    = EventManager<MouseMoveEvent>::get();
	auto& mouse_press_event_mgr   = EventManager<MousePressEvent>::get();
	auto& mouse_release_event_mgr = EventManager<MouseReleaseEvent>::get();
	auto& window_close_event_mgr  = EventManager<WindowCloseEvent>::get();
}

/* static */ void Input::update() noexcept
{
	Mouse::set_dx(0);
	Mouse::set_dy(0);

	// TODO: Oh... rewrite. use only dx and dy
	Window root_ret, child_ret;
	int root_x_ret, root_y_ret, win_x_ret, win_y_ret;
	unsigned mask_ret;
	auto dpy = os::Descriptor::get();
	XQueryPointer(dpy, RootWindow(dpy, 0),
		&root_ret, &child_ret, &root_x_ret, &root_y_ret, &win_x_ret, &win_y_ret, &mask_ret);

	static int mx;
	static int my;

	//mx += win_x_ret - 1800;
	//my += win_y_ret - 800;
	//mouse_move_event_mgr.send(mx, my);
	//sys::Mouse::set_position(1800, 800);

	XEvent event;
	int event_count;
	while ((event_count = XPending(dpy))) {
		do {
			XNextEvent(dpy, &event);
			switch (event.type) {
				case KeyPress:      key_press_event_mgr.send(keyboard_btn_map[event.xkey.keycode]); break;
				case KeyRelease:    key_release_event_mgr.send(keyboard_btn_map[event.xkey.keycode]); break;
				case MotionNotify:  mouse_move_event_mgr.send(event.xmotion.x, event.xmotion.y); break;
				case ButtonPress:   mouse_press_event_mgr.send((MouseBtn)event.xbutton.button); break;
				case ButtonRelease: mouse_release_event_mgr.send((MouseBtn)event.xbutton.button); break;
				case ClientMessage: window_close_event_mgr.send(); break;
			}
		} while (--event_count);
	}
}

/* static */ Status Input::create() noexcept
{
	static_assert((int)KeyboardBtn::UNKNOWN == 0,
		"static variable equals to zero (.bss segment), fill with UNKNOWN manually");
	/* memset(keyboard_btn_map, (int)KeyboardBtn::UNKNOWN, sizeof(keyboard_btn_map)); */

	keyboard_btn_map[KEY(1)]   = KeyboardBtn::ESCAPE;
	keyboard_btn_map[KEY(15)]  = KeyboardBtn::TAB;
	keyboard_btn_map[KEY(57)]  = KeyboardBtn::SPACE;
	keyboard_btn_map[KEY(28)]  = KeyboardBtn::ENTER;
	keyboard_btn_map[KEY(111)] = KeyboardBtn::DELETE;
	keyboard_btn_map[KEY(14)]  = KeyboardBtn::BACK_SPACE;
	keyboard_btn_map[KEY(58)]  = KeyboardBtn::CAPS_LOCK;
	keyboard_btn_map[KEY(102)] = KeyboardBtn::HOME;
	keyboard_btn_map[KEY(107)] = KeyboardBtn::END;
	keyboard_btn_map[KEY(104)] = KeyboardBtn::PAGE_UP;
	keyboard_btn_map[KEY(109)] = KeyboardBtn::PAGE_DOWN;
	keyboard_btn_map[KEY(103)] = KeyboardBtn::UP_ARROW;
	keyboard_btn_map[KEY(108)] = KeyboardBtn::DOWN_ARROW;
	keyboard_btn_map[KEY(105)] = KeyboardBtn::LEFT_ARROW;
	keyboard_btn_map[KEY(106)] = KeyboardBtn::RIGHT_ARROW;

	keyboard_btn_map[KEY(12)]  = KeyboardBtn::MINUS;
	keyboard_btn_map[KEY(13)]  = KeyboardBtn::EQUAL;

	keyboard_btn_map[KEY(42)]  = KeyboardBtn::LEFT_SHIFT;
	keyboard_btn_map[KEY(54)]  = KeyboardBtn::RIGHT_SHIFT;
	keyboard_btn_map[KEY(29)]  = KeyboardBtn::LEFT_CTRL;
	keyboard_btn_map[KEY(97)]  = KeyboardBtn::RIGHT_CTRL;
	keyboard_btn_map[KEY(56)]  = KeyboardBtn::LEFT_ALT;
	keyboard_btn_map[KEY(100)] = KeyboardBtn::RIGHT_ALT;

	keyboard_btn_map[KEY(41)] = KeyboardBtn::TILDE;
	keyboard_btn_map[KEY(26)] = KeyboardBtn::LEFT_BRACKET;
	keyboard_btn_map[KEY(27)] = KeyboardBtn::RIGHT_BRACKET;
	keyboard_btn_map[KEY(43)] = KeyboardBtn::BACKSLASH;
	keyboard_btn_map[KEY(39)] = KeyboardBtn::SEMI_COLON;
	keyboard_btn_map[KEY(40)] = KeyboardBtn::QUOTE;
	keyboard_btn_map[KEY(51)] = KeyboardBtn::COMMA;
	keyboard_btn_map[KEY(52)] = KeyboardBtn::PERIOD;
	keyboard_btn_map[KEY(53)] = KeyboardBtn::SLASH;

	/* num row */
	keyboard_btn_map[KEY(59)] = KeyboardBtn::F1;
	keyboard_btn_map[KEY(60)] = KeyboardBtn::F2;
	keyboard_btn_map[KEY(61)] = KeyboardBtn::F3;
	keyboard_btn_map[KEY(62)] = KeyboardBtn::F4;
	keyboard_btn_map[KEY(63)] = KeyboardBtn::F5;
	keyboard_btn_map[KEY(64)] = KeyboardBtn::F6;
	keyboard_btn_map[KEY(65)] = KeyboardBtn::F7;
	keyboard_btn_map[KEY(66)] = KeyboardBtn::F8;
	keyboard_btn_map[KEY(67)] = KeyboardBtn::F9;
	keyboard_btn_map[KEY(68)] = KeyboardBtn::F10;
	keyboard_btn_map[KEY(69)] = KeyboardBtn::F11;
	keyboard_btn_map[KEY(70)] = KeyboardBtn::F12;

	/* num row */
	keyboard_btn_map[KEY(2)] = KeyboardBtn::BTN_1;
	keyboard_btn_map[KEY(3)] = KeyboardBtn::BTN_2;
	keyboard_btn_map[KEY(4)] = KeyboardBtn::BTN_3;
	keyboard_btn_map[KEY(5)] = KeyboardBtn::BTN_4;
	keyboard_btn_map[KEY(6)] = KeyboardBtn::BTN_5;
	keyboard_btn_map[KEY(7)] = KeyboardBtn::BTN_6;
	keyboard_btn_map[KEY(8)] = KeyboardBtn::BTN_7;
	keyboard_btn_map[KEY(9)] = KeyboardBtn::BTN_8;
	keyboard_btn_map[KEY(10)] = KeyboardBtn::BTN_9;
	keyboard_btn_map[KEY(11)] = KeyboardBtn::BTN_0;

	/* top row */
	keyboard_btn_map[KEY(16)] = KeyboardBtn::Q;
	keyboard_btn_map[KEY(17)] = KeyboardBtn::W;
	keyboard_btn_map[KEY(18)] = KeyboardBtn::E;
	keyboard_btn_map[KEY(19)] = KeyboardBtn::R;
	keyboard_btn_map[KEY(20)] = KeyboardBtn::T;
	keyboard_btn_map[KEY(21)] = KeyboardBtn::Y;
	keyboard_btn_map[KEY(22)] = KeyboardBtn::U;
	keyboard_btn_map[KEY(23)] = KeyboardBtn::I;
	keyboard_btn_map[KEY(24)] = KeyboardBtn::O;
	keyboard_btn_map[KEY(25)] = KeyboardBtn::P;

	/* middle row */
	keyboard_btn_map[KEY(30)] = KeyboardBtn::A;
	keyboard_btn_map[KEY(31)] = KeyboardBtn::S;
	keyboard_btn_map[KEY(32)] = KeyboardBtn::D;
	keyboard_btn_map[KEY(33)] = KeyboardBtn::F;
	keyboard_btn_map[KEY(34)] = KeyboardBtn::G;
	keyboard_btn_map[KEY(35)] = KeyboardBtn::H;
	keyboard_btn_map[KEY(36)] = KeyboardBtn::J;
	keyboard_btn_map[KEY(37)] = KeyboardBtn::K;
	keyboard_btn_map[KEY(38)] = KeyboardBtn::L;

	/* bottom row */
	keyboard_btn_map[KEY(44)] = KeyboardBtn::Z;
	keyboard_btn_map[KEY(45)] = KeyboardBtn::X;
	keyboard_btn_map[KEY(46)] = KeyboardBtn::C;
	keyboard_btn_map[KEY(47)] = KeyboardBtn::V;
	keyboard_btn_map[KEY(48)] = KeyboardBtn::B;
	keyboard_btn_map[KEY(49)] = KeyboardBtn::N;
	keyboard_btn_map[KEY(50)] = KeyboardBtn::M;

	DK_LOG_OK("Input system created");
	return Status::OK;
}

}
