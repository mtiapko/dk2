#version 330 core

uniform mat4 view_mat;
uniform float val;

layout (location = 0) in vec3 attr_vert_pos;
layout (location = 1) in vec3 attr_vert_norm;
layout (location = 2) in vec2 attr_vert_uv;

varying vec3 vert_norm;
varying vec2 vert_uv;

void main()
{
	vert_norm = attr_vert_norm;
	vert_uv = attr_vert_uv;

	mat4 view = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(0, 0, 0, 1)
	);

	float a = val * 3.1415926 / 180.0;
	float c = cos(a);
	float s = sin(a);
	mat4 model = mat4(
#if 0
		vec4(0.2, 0, 0, 0),
		vec4(0, 0.2, 0, 0),
		vec4(0, 0, 0.1, 0),
		vec4(0, 0, 0, 1)
#else
		vec4(c * 0.1, 0, s, 0),
		vec4(0, 0.1, 0, 0),
		vec4(-s, 0, c * 0.1, 0),
		vec4(0, 0, 0, 1)
#endif
	);

	gl_Position = model * vec4(attr_vert_pos, 1.0);
}
