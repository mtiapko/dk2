#version 330 core

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

layout (location = 0) in vec3 attr_vert_pos;
layout (location = 1) in vec3 attr_vert_norm;
layout (location = 2) in vec2 attr_vert_uv;

varying vec3 vert_norm;
varying vec2 vert_uv;

void main()
{
	vert_norm = attr_vert_norm;
	vert_uv = attr_vert_uv;

	mat4 proj = proj_mat;
	mat4 view = view_mat;
	mat4 model = model_mat;

	gl_Position = vec4(attr_vert_pos, 1.0) * model * view * proj;
}
