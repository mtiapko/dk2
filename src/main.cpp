#include "log.h"
#include "core.h"
#include "audio/source.h"
#include "audio/listener.h"
#include "graph/shader_program.h"
#include "sys/events/window_close_event.h"
#include "sys/event_listener.h"
#include "sys/event_manager.h"
#include "sys/keyboard.h"
#include "sys/mouse.h"

using namespace dk;

class test_app : public application, sys::event_listener<sys::window_close_event>
{
private:
	audio::source         m_speaker;
	audio::sound          m_sint;
	graph::window*        m_wnd;
	graph::shader_program m_shader;

public:
	~test_app() noexcept override
	{
		this->destroy();
	}

	void handle(const sys::window_close_event&) noexcept override
	{
		core::stop();
	}

	void update(float) noexcept override
	{
		bool changed = false;
		if (sys::keyboard::state(sys::keyboard_btn::UP_ARROW)) {
			m_speaker.set_pitch(m_speaker.pitch() + 0.01f);
			changed = true;
		}

		if (sys::keyboard::state(sys::keyboard_btn::DOWN_ARROW)) {
			m_speaker.set_pitch(m_speaker.pitch() - 0.01f);
			changed = true;
		}

		if (changed)
			DK_LOG("pitch val: ", m_speaker.pitch());
	}

	void render() noexcept override
	{
		m_wnd->render();
	}

	status create() noexcept override
	{
		auto renderer = core::active<graph::renderer>();
		m_wnd = renderer->create_window();
		if (auto ret = m_wnd->create(); !ret)
			return ret;

		if (auto ret = m_speaker.create(); !ret)
			return ret;

		if (auto ret = m_sint.create("res/audio/sint.wav"); !ret)
			return ret;

		if (auto ret = m_shader.create(); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/default_vert.glsl", graph::shader_type::VERTEX); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/default_frag.glsl", graph::shader_type::FRAGMENT); !ret)
			return ret;

		if (auto ret = m_shader.link(); !ret)
			return ret;

		audio::listener::create();
		m_speaker.set_gain(1.0f);
		m_speaker.set_pitch(1.0f);
		//m_speaker.set(m_sint);
		//m_speaker.play();

		sys::event_manager<sys::window_close_event>::get().subscribe(this);
		sys::mouse::record_input(true);
		sys::keyboard::record_input(true);
		return status::OK;
	}

	void destroy() noexcept override
	{
		m_speaker.remove_sound();
	}
};

int main()
{
	if (auto ret = core::create(); !ret)
		return ret;

	{
		test_app app;
		if (auto ret = core::run(&app); !ret)
			return ret;

		DK_LOG_OK("Application destroyed");
	}

	core::destroy();
	return 0;
}
