#include <GL/glew.h>
#include "log.h"
#include "core.h"
#include "audio/source.h"
#include "audio/listener.h"
#include "graph/texture.h"
#include "graph/shader_program.h"
#include "sys/resource_manager.h"
#include "sys/events/window_close_event.h"
#include "sys/event_listener.h"
#include "sys/event_manager.h"
#include "sys/keyboard.h"
#include "sys/mouse.h"

using namespace dk;

class test_app final: public application, sys::event_listener<sys::window_close_event>
{
private:
	audio::source         m_speaker;
	audio::sound          m_sint;
	audio::sound*         m_sint_2;
	graph::window*        m_wnd;
	graph::shader_program m_shader;
	graph::texture        m_texture;

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

		if (sys::keyboard::state(sys::keyboard_btn::A)) {
			m_speaker.stop();
			m_speaker.set(*m_sint_2);
			m_speaker.play();
		} else if (sys::keyboard::state(sys::keyboard_btn::D)) {
			m_speaker.stop();
			m_speaker.set(m_sint);
			m_speaker.play();
		}

		if (sys::keyboard::state(sys::keyboard_btn::W)) {
			m_speaker.set_sec_offset(m_speaker.sec_offset() + 10.0f);
			DK_LOG("track time: ", m_speaker.sec_offset(), "s (+10s)");
		} else if (sys::keyboard::state(sys::keyboard_btn::S)) {
			m_speaker.set_sec_offset(m_speaker.sec_offset() - 10.0f);
			DK_LOG("track time: ", m_speaker.sec_offset(), "s (-10s)");
		}

		if (sys::keyboard::state(sys::keyboard_btn::R))
			m_speaker.rewind();

		if (sys::keyboard::state(sys::keyboard_btn::ESCAPE))
			core::stop();

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

		if (auto ret = sys::resource_manager::load(m_sint, "res/audio/sint.wav"); !ret)
			return ret;

		if ((m_sint_2 = sys::resource_manager::load<audio::sound>("res/audio/Omnia & IRA - The Fusion.wav")) == nullptr)
			return status::ERROR;

		if (auto ret = sys::resource_manager::load(m_texture, "res/tex/stallTexture.png"); !ret)
			return ret;

		if (auto ret = m_shader.create(); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/vert.glsl", graph::shader_type::VERTEX); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/frag.glsl", graph::shader_type::FRAGMENT); !ret)
			return ret;

		if (auto ret = m_shader.link(); !ret)
			return ret;

		audio::listener::create();
		m_speaker.set_gain(1.0f);
		m_speaker.set_pitch(1.0f);
		m_speaker.set(*m_sint_2);
		m_speaker.play();

		sys::event_manager<sys::window_close_event>::get().subscribe(this);
		sys::mouse::record_input(true);
		sys::keyboard::record_input(true);

		// Set up vertex data (and buffer(s)) and attribute pointers
		GLfloat vertices[] = {
			// Positions          // Colors           // Texture Coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3, // First Triangle
			1, 2, 3  // Second Triangle
		};
		GLuint VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		// Draw container
		m_shader.enable();
		m_texture.enable();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		return status::OK;
	}

	void destroy() noexcept override
	{
		m_speaker.remove_sound();
	}
};

int main()
{
	status ret;
	if ((ret = core::create())) {
		test_app app;
		ret = core::run(&app);
		DK_LOG_OK("Application destroyed");
	}

	core::destroy();
	return ret;
}
