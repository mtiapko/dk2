#version 330 core

uniform mat4 proj_mat;
uniform mat4 view_mat;

layout (location = 0) in vec3 attr_vert_pos;

varying vec3 vert_uv;

void main()
{
	vert_uv = attr_vert_pos;

	mat4 view = mat4(mat3(view_mat));
	vec4 pos = vec4(attr_vert_pos, 1.0) * view * proj_mat;
	gl_Position = pos.xyww;
}
