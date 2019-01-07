#include "log.h"
#include "core.h"
#include "audio/core.h"
#include "audio/sound.h"
#include "audio/source.h"
#include "audio/listener.h"
#include "sys/keyboard.h"
#include "sys/mouse.h"

using namespace dk;

class test_app : public dk::application
{
private:
	audio::source  m_speaker;
	audio::sound   m_sint;
	graph::window* m_wnd;

public:
	~test_app() noexcept override
	{
		this->destroy();
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
			DK_LOG("pitch val: ", m_speaker.pitch(), ", mouse: (", sys::mouse::x(), ", ", sys::mouse::y(), ')');
	}

	void render() noexcept override
	{
		m_wnd->render();
	}

	status create() noexcept override
	{
		if (auto res = audio::core::create(); !res)
			return res;

		auto renderer = core::active<graph::renderer>();
		m_wnd = renderer->create_window();
		if (auto res = m_wnd->create(); !res)
			return res;

		if (auto res = m_speaker.create(); !res)
			return res;

		audio::sound_data sint_data;
		if (auto res = sint_data.create("res/audio/atc-around_the_world.wav"); !res)
			return res;

		if (auto res = m_sint.create(sint_data); !res)
			return res;

		audio::listener::create();
		m_speaker.set_gain(1.0f);
		m_speaker.set_pitch(1.0f);
		m_speaker.set_sound(m_sint);
		m_speaker.play();

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
	if (auto res = core::create(); !res)
		return res;

	test_app app;
	if (auto res = core::run(&app); !res)
		return res;

	return 0;
}
