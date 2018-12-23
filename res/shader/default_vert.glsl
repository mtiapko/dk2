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
