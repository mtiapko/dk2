#include <GL/glew.h>
#include "Log.h"
#include "Core.h"
#include "audio/Source.h"
#include "audio/Listener.h"
#include "graph/Model.h"
#include "graph/Texture.h"
#include "graph/ShaderProgram.h"
#include "sys/ResourceManager.h"
#include "sys/events/WindowCloseEvent.h"
#include "sys/EventListener.h"
#include "sys/EventManager.h"
#include "sys/Keyboard.h"
#include "sys/Mouse.h"

using namespace dk;

class test_app final: public Application, sys::EventListener<sys::WindowCloseEvent>
{
private:
	audio::Source        m_speaker;
	audio::Sound         m_sint;
	audio::Sound*        m_sint_2;
	graph::Window*       m_wnd;
	graph::ShaderProgram m_shader;
	graph::Texture       m_texture;
	graph::Model         m_stall;

public:
	~test_app() noexcept override
	{
		this->destroy();
	}

	void handle(const sys::WindowCloseEvent&) noexcept override
	{
		Core::stop();
	}

	void update(float) noexcept override
	{
		bool changed = false;
		if (sys::Keyboard::state(sys::KeyboardBtn::UP_ARROW)) {
			m_speaker.set_pitch(m_speaker.pitch() + 0.01f);
			changed = true;
		}

		if (sys::Keyboard::state(sys::KeyboardBtn::DOWN_ARROW)) {
			m_speaker.set_pitch(m_speaker.pitch() - 0.01f);
			changed = true;
		}

		if (sys::Keyboard::state(sys::KeyboardBtn::A)) {
			m_speaker.stop();
			m_speaker.set(*m_sint_2);
			m_speaker.play();
		} else if (sys::Keyboard::state(sys::KeyboardBtn::D)) {
			m_speaker.stop();
			m_speaker.set(m_sint);
			m_speaker.play();
		}

		if (sys::Keyboard::state(sys::KeyboardBtn::W)) {
			m_speaker.set_sec_offset(m_speaker.sec_offset() + 10.0f);
			DK_LOG("track time: ", m_speaker.sec_offset(), "s (+10s)");
		} else if (sys::Keyboard::state(sys::KeyboardBtn::S)) {
			m_speaker.set_sec_offset(m_speaker.sec_offset() - 10.0f);
			DK_LOG("track time: ", m_speaker.sec_offset(), "s (-10s)");
		}

		if (sys::Keyboard::state(sys::KeyboardBtn::R))
			m_speaker.rewind();

		if (sys::Keyboard::state(sys::KeyboardBtn::ESCAPE))
			Core::stop();

		if (changed)
			DK_LOG("pitch val: ", m_speaker.pitch());
	}

	void render() noexcept override
	{
		m_shader.enable();
		m_texture.enable();
		m_stall.render();
		m_wnd->render();
	}

	Status create() noexcept override
	{
		auto renderer = Core::active<graph::Renderer>();
		m_wnd = renderer->create_window();
		if (auto ret = m_wnd->create(); !ret)
			return ret;

		if (auto ret = m_speaker.create(); !ret)
			return ret;

		if (auto ret = sys::ResourceManager::load(m_sint, "res/audio/sint.wav"); !ret)
			return ret;

		if (auto ret = sys::ResourceManager::load(m_stall, "res/model/stall.obj"); !ret)
			return ret;

		if ((m_sint_2 = sys::ResourceManager::load<audio::Sound>("res/audio/Omnia & IRA - The Fusion.wav")) == nullptr)
			return Status::ERROR;

		if (auto ret = sys::ResourceManager::load(m_texture, "res/tex/stallTexture.png"); !ret)
			return ret;

		if (auto ret = m_shader.create(); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/vert.glsl", graph::ShaderType::VERTEX); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/frag.glsl", graph::ShaderType::FRAGMENT); !ret)
			return ret;

		if (auto ret = m_shader.link(); !ret)
			return ret;

		audio::Listener::create();
		m_speaker.set_gain(1.0f);
		m_speaker.set_pitch(1.0f);
		m_speaker.set(*m_sint_2);
		m_speaker.play();

		sys::EventManager<sys::WindowCloseEvent>::get().subscribe(this);
		sys::Mouse::record_input(true);
		sys::Keyboard::record_input(true);
		return Status::OK;
	}

	void destroy() noexcept override
	{
		m_speaker.remove_sound();
	}
};

int main()
{
	Status ret;
	if ((ret = Core::create())) {
		test_app app;
		ret = Core::run(&app);
		DK_LOG_OK("Application destroyed");
	}

	Core::destroy();
	return ret;
}
