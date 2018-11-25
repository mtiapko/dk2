#include <GL/glew.h>
#include "log.h"
#include "app.h"
#include "core.h"
#include "graphic/gl.h"
#include "graphic/mesh.h"
#include "graphic/render_system.h"
#include "containers/string_view.h"

dk::string_view vert_src{ R"glsl(
	#version 330 core
	layout(location = 0) in vec3 vertexPosition_modelspace;
	uniform mat4 mat;
	void main(){
		gl_Position = mat * vec4(vertexPosition_modelspace, 1);
	}
)glsl" };

dk::string_view frag_src{ R"glsl(
	#version 330 core
	out vec3 color;
		void main(){
		color = vec3(1,sin(gl_FragCoord.x * gl_FragCoord.y),cos(gl_FragCoord.x / gl_FragCoord.y));
	}
)glsl" };

class test_app : public dk::application
{
private:
	dk::render_window* wnd;
	dk::mesh house;
	dk::mat4f mat;
	dk::shader_program prog;

public:
	void update() override
	{
		//mat *= mat.get_rot_y(2.0f);
		auto location = prog.get_uniform_location("mat");
		GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, mat.data));
	}

	void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLES, 0, house.m_indices.size());
		GL_CALL(glDrawElements(GL_TRIANGLES, house.m_indices.size(), GL_UNSIGNED_INT, nullptr));
		wnd->render();
	}

	dk::status create() override
	{
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

		if (house.load("res/cube.obj") != dk::status::OK)
			return dk::status::ERROR;

		/*static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};*/

		GLuint VertexArrayID;
		GL_CALL(glGenVertexArrays(1, &VertexArrayID));
		GL_CALL(glBindVertexArray(VertexArrayID));

		GLuint vertexbuffer;
		GL_CALL(glGenBuffers(1, &vertexbuffer));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, house.m_vertices.size() * sizeof(house.m_vertices[0]), house.m_vertices.data(), GL_STATIC_DRAW));

		GLuint indexbuffer;
		GL_CALL(glGenBuffers(1, &indexbuffer));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, house.m_indices.size() * sizeof(house.m_indices[0]), house.m_indices.data(), GL_STATIC_DRAW));

		GL_CALL(glEnableVertexAttribArray(0));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

		prog.enable();
		GL_CALL(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));

		//mat.unit();
		mat = dk::mat4f(1);
		//mat.perspective(120.0f, 800.0f / 600.0f, 0.1f, 10.0f);
		//mat.translate(dk::vec4f(0, -2, -3, 1));
		mat *= mat.get_translate(dk::vec4f(0, 0, -1, 1));
		mat *= mat.get_perspective(120.0f, 800.0f / 600.0f, 0.1f, 10.0f);
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
	if (dk::core::create(&app) != dk::status::OK)
		return -1;

	if (dk::core::run() != dk::status::OK)
		return -1;

	return 0;
}
