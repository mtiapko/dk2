#include "containers/string_view.h"

dk::string_view vert_src{ R"glsl(
	#version 330 core
	layout(location = 0) in vec3 vertexPosition_modelspace;
	layout(location = 1) in vec3 norm;
	layout(location = 2) in vec3 in_tex_coord;
	uniform mat4 mat;
	varying vec3 my_norm;
	varying vec2 tex_coord;
	void main(){
		my_norm = norm;
		tex_coord = in_tex_coord.xy;
		gl_Position = vec4(vertexPosition_modelspace, 1) * mat;
	}
)glsl" };

dk::string_view frag_src{ R"glsl(
	#version 330 core
	uniform sampler2D tex;
	out vec3 color;
	varying vec3 my_norm;
	varying vec2 tex_coord;
	void main(){
		//color = vec3(gl_FragCoord.z);
		color = texture(tex, vec2(tex_coord.x, 1.0 - tex_coord.y)).rgb;
	}
)glsl" };
