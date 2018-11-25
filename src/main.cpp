#include <GL/glew.h>
#include "log.h"
#include "app.h"
#include "core.h"
#include "graphic/gl_call.h"
#include "graphic/render_system.h"
#include "containers/string_view.h"

dk::string_view vert_src{ R"glsl(
	#version 330 core
	layout(location = 0) in vec3 vertexPosition_modelspace;
	void main(){
		gl_Position.xyz = vertexPosition_modelspace;
		gl_Position.w = 1.0;
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

public:
	void update() override
	{
		/* update me! */
	}

	void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		wnd->render();
	}

	dk::ret_code create() override
	{
		auto render_sys = dk::core::get_render_sys();
		if (render_sys == nullptr)
			return dk::ret_code::ERROR;

		wnd = render_sys->create_window();
		if (wnd == nullptr)
			return dk::ret_code::ERROR;

		if (wnd->create() != dk::ret_code::OK)
			return dk::ret_code::ERROR;

		dk::shader frag;
		if (frag.create(dk::shader_type::FRAGMENT_SHADER, frag_src) != dk::ret_code::OK)
			return dk::ret_code::ERROR;

		dk::shader vert;
		if (vert.create(dk::shader_type::VERTEX_SHADER, vert_src) != dk::ret_code::OK)
			return dk::ret_code::ERROR;

		dk::shader_program prog;
		prog.create();
		prog.add_shader(vert);
		prog.add_shader(frag);
		if (prog.link() != dk::ret_code::OK)
			return dk::ret_code::ERROR;

		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};

		GLuint VertexArrayID;
		GL_CALL(glGenVertexArrays(1, &VertexArrayID));
		GL_CALL(glBindVertexArray(VertexArrayID));

		GLuint vertexbuffer;
		GL_CALL(glGenBuffers(1, &vertexbuffer));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

		GL_CALL(glEnableVertexAttribArray(0));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
		GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

		prog.enable();
		GL_CALL(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		return dk::ret_code::OK;
	}
};

int main()
{
	test_app app;
	if (dk::core::create(&app) != dk::ret_code::OK)
		return -1;

	if (dk::core::run() != dk::ret_code::OK)
		return -1;

	return 0;
}
