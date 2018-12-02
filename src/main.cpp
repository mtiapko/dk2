# include <GL/glew.h>
#include "tmp.h"
#include "log.h"
#include "app.h"
#include "core.h"
#include "event_system.h"
#include "events/create_event.h"
#include "events/destroy_event.h"
#include "events/update_event.h"
#include "events/render_event.h"
#include "graphic/gl.h"
#include "graphic/mesh.h"
#include "graphic/texture.h"
#include "graphic/render_system.h"
#include "containers/string_view.h"

class test_app : public dk::application,
	dk::event_listener<dk::create_event>,
	dk::event_listener<dk::update_event>,
	dk::event_listener<dk::render_event>
{
private:
	dk::render_window* wnd;
	dk::mesh house;
	dk::texture obj_tex;
	dk::mat4f mat;
	dk::shader_program prog;

public:
	test_app()
	{
		dk::event_system<dk::create_event>::get().subscribe(this);
	}

	void handle(const dk::create_event&) override
	{
		if (this->create() != dk::status::OK)
			dk::event_system<dk::destroy_event>::get().send();
	}

	void handle(const dk::update_event&) override
	{
		this->update();
	}

	void handle(const dk::render_event&) override
	{
		this->render();
	}

	void update() override
	{
		mat *= mat.get_rot_y(1.0f);
		mat *= mat.get_rot_x(1.0f);
	}

	void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		prog.enable();
		auto location = prog.get_uniform_location("mat");
		GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, mat.data));
		GL_CALL(glDrawElements(GL_TRIANGLES, house.m_indices.size(), GL_UNSIGNED_INT, nullptr));

		wnd->render();
	}

	dk::status create() override
	{
		dk::event_system<dk::update_event>::get().subscribe(this);
		dk::event_system<dk::render_event>::get().subscribe(this);

		auto render_sys = dk::core::get_render_sys();
		if (render_sys == nullptr)
			return dk::status::ERROR;

		wnd = render_sys->create_window();
		if (wnd == nullptr)
			return dk::status::ERROR;

		if (wnd->create() != dk::status::OK)
			return dk::status::ERROR;

		dk::shader frag;
		if (frag.create(dk::shader_type::FRAGMENT_SHADER, frag_src) != dk::status::OK)
			return dk::status::ERROR;

		dk::shader vert;
		if (vert.create(dk::shader_type::VERTEX_SHADER, vert_src) != dk::status::OK)
			return dk::status::ERROR;

		prog.create();
		prog.add_shader(vert);
		prog.add_shader(frag);
		if (prog.link() != dk::status::OK)
			return dk::status::ERROR;

		if (house.load("res/house.obj") != dk::status::OK)
			return dk::status::ERROR;

		if (obj_tex.create("res/old_house/DSC_5871_.jpg") != dk::status::OK)
			return dk::status::ERROR;

		obj_tex.enable();

		GLuint VertexArrayID;
		GL_CALL(glGenVertexArrays(1, &VertexArrayID));
		GL_CALL(glBindVertexArray(VertexArrayID));

		GLuint indexbuffer;
		GL_CALL(glGenBuffers(1, &indexbuffer));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, house.m_indices.size() * sizeof(house.m_indices[0]), house.m_indices.data(), GL_STATIC_DRAW));

		/* vert */
		GLuint vertexbuffer;
		GL_CALL(glGenBuffers(1, &vertexbuffer));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, house.m_vertices.size() * sizeof(house.m_vertices[0]), house.m_vertices.data(), GL_STATIC_DRAW));

		GL_CALL(glEnableVertexAttribArray(0));
		GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

		/* normal */
		GL_CALL(glGenBuffers(1, &vertexbuffer));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, house.m_normals.size() * sizeof(house.m_normals[0]), house.m_normals.data(), GL_STATIC_DRAW));

		GL_CALL(glEnableVertexAttribArray(1));
		GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

		/* uv */
		GL_CALL(glGenBuffers(1, &vertexbuffer));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, house.m_uvs.size() * sizeof(house.m_uvs[0]), house.m_uvs.data(), GL_STATIC_DRAW));

		GL_CALL(glEnableVertexAttribArray(2));
		GL_CALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

		GL_CALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

		//mat.unit();
		mat = dk::mat4f(1.0);
		mat = mat.get_orthographic(-350, 350, -350, 350, 0.1, 2000) * mat.get_translate(dk::vec4f(0, -0, -800.0));
		//mat = mat.get_perspective(90.0, 800.0f / 600.0f, 0.3, 15) * mat.get_translate(dk::vec4f(3, 3, -5.6));
		//mat.orthographic(-10, 10, -10, 10, -10.0, 15);
		//mat = mat.get_perspective(130.0f, 800.0f / 600.0f, 0.1, 100.0f);
		//mat.translate(dk::vec4f(0, 0, -1.5));
		GL_CALL(glEnable(GL_DEPTH_TEST));
		//mat.translate(dk::vec4f(0, -2, -3, 1));
		//mat *= mat.get_translate(dk::vec4f(0, 0, -1, 1));
		//mat *= mat.get_perspective(120.0f, 800.0f / 600.0f, 0.1f, 10.0f);
		/*for (size_t i = 0; i < 4; ++i) {
			for (size_t j = 0; j < 4; ++j) {
				std::clog << mat.data[i * 4 + j] << ' ';
			}

			std::clog << '\n';
		}*/
		//mat = mat.get_translate(dk::vec4f(0, 0, -15)) * mat.get_perspective(120.0f, 800.0f / 600.0f, 0.1f, 500.0f);
		//mat = mat.get_translate(dk::vec4f(0, 0, 105, 1));

		return dk::status::OK;
	}
};

int main()
{
	test_app app;
	if (dk::core::create() != dk::status::OK)
		return -1;

	if (dk::core::run() != dk::status::OK)
		return -1;

	return 0;
}
