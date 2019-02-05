#include <GL/glew.h>
#include "Log.h"
#include "Core.h"
#include "ResourceManager.h"
#include "audio/Source.h"
#include "audio/Listener.h"
#include "graph/GUI.h"
#include "graph/CubeMap.h"
#include "graph/Camera.h"
#include "graph/Model.h"
#include "graph/Texture.h"
#include "graph/ShaderProgram.h"
#include "sys/events/WindowCloseEvent.h"
#include "sys/EventListener.h"
#include "sys/EventManager.h"
#include "sys/Keyboard.h"
#include "sys/Mouse.h"

using namespace dk;

class test_app final: public Application, sys::EventListener<sys::WindowCloseEvent>
{
private:
	ResourceManager        m_res_mgr;

	audio::Source          m_speaker;
	audio::Sound           m_sint;
	audio::Sound*          m_sint_2;
	graph::Window*         m_wnd;
	graph::Texture         m_texture;
	graph::Model           m_stall;
	graph::Camera          m_camera;

	graph::ShaderProgram   m_shader;
	graph::UniformLocation m_view_loc;
	graph::UniformLocation m_proj_loc;

	graph::CubeMap         m_cube_map;
	graph::CubeMapTexture  m_cube_map_tex;
	graph::ShaderProgram   m_cube_map_shader;
	graph::UniformLocation m_cube_map_view_loc;
	graph::UniformLocation m_cube_map_proj_loc;

	float m_val = 0.0f;

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
		if (sys::Keyboard::state(sys::KeyboardBtn::R))
			m_speaker.rewind();

		if (sys::Keyboard::state(sys::KeyboardBtn::ESCAPE))
			Core::stop();

		m_camera.update();
		graph::GUI::update();
	}

	void render() noexcept override
	{
		m_wnd->clear();
		auto view = m_camera.view();

		m_cube_map_shader.enable();
		m_shader.set_uniform(m_cube_map_view_loc, view);
		m_cube_map.render();

		m_shader.enable();
		m_shader.set_uniform(m_view_loc, view);
		m_texture.enable();
		m_stall.render();

		/* GUI */
		ImGui::Begin("Matrix");
		ImGui::SliderFloat("Rot Y", &m_val, 0.0f, 360.0f);
		ImGui::End();

		graph::GUI::render();
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

		if (auto ret = m_res_mgr.load(m_sint, "res/audio/sint.wav"); !ret)
			return ret;

		if (auto ret = m_res_mgr.load(m_stall, "res/model/stall.obj"); !ret)
			return ret;

		if ((m_sint_2 = m_res_mgr.load<audio::Sound>("res/audio/sint.wav")) == nullptr)
			return Status::ERROR;

		if (auto ret = m_res_mgr.load(m_texture, "res/tex/stallTexture.png"); !ret)
			return ret;

		/* basic shader */
		if (auto ret = m_shader.create(); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/vert.glsl", graph::ShaderType::VERTEX); !ret)
			return ret;

		if (auto ret = m_shader.add("res/shader/frag.glsl", graph::ShaderType::FRAGMENT); !ret)
			return ret;

		if (auto ret = m_shader.link(); !ret)
			return ret;

		auto proj = math::Mat4f::get_perspective(90.0f, m_wnd->ratio(), 0.1f, 100.0f);
		m_shader.enable();
		m_shader.uniform_location("view_mat", m_view_loc);
		m_shader.uniform_location("proj_mat", m_proj_loc);
		m_shader.set_uniform(m_proj_loc, proj);

		/* cube map shader */
		if (auto ret = m_cube_map_shader.create(); !ret)
			return ret;

		if (auto ret = m_cube_map_shader.add("res/shader/cube_map_vert.glsl", graph::ShaderType::VERTEX); !ret)
			return ret;

		if (auto ret = m_cube_map_shader.add("res/shader/cube_map_frag.glsl", graph::ShaderType::FRAGMENT); !ret)
			return ret;

		if (auto ret = m_cube_map_shader.link(); !ret)
			return ret;

		m_cube_map_shader.enable();
		m_cube_map_shader.uniform_location("view_mat", m_cube_map_view_loc);
		m_cube_map_shader.uniform_location("proj_mat", m_cube_map_proj_loc);
		m_cube_map_shader.set_uniform(m_cube_map_proj_loc, proj);

		if (auto ret = renderer->init_module<graph::CubeMap>(); !ret)
			return ret;

		if (auto ret = m_cube_map_tex.create(
				"res/skybox/right.jpg",
				"res/skybox/left.jpg",
				"res/skybox/top.jpg",
				"res/skybox/bottom.jpg",
				"res/skybox/front.jpg",
				"res/skybox/back.jpg"
		); !ret)
			return ret;

		if (auto ret = m_cube_map.create(m_cube_map_tex); !ret)
			return ret;

		audio::Listener::create();
		m_speaker.set_gain(1.0f);
		m_speaker.set_pitch(1.0f);
		m_speaker.set(*m_sint_2);
		//m_speaker.play();

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
