#version 330 core
precision mediump float;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;

uniform mat4 view_proj;
out vec2 uv;
out vec3 world_space_pos;
out vec3 vertex_pos;
out vec3 norm;
out mat3 TBN;

const float PI = 3.1415926;

#define TO_RAD(x) ((x) * PI / 180.0)

mat4 rot_x(float rad)
{
	float s = sin(rad);
	float c = cos(rad);
	return mat4(
		1, 0,  0, 0,
		0, c, -s, 0,
		0, s,  c, 0,
		0, 0,  0, 1
	);
}

void main()
{
	const float scale = 1.0;
	mat4 model = mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1
	) * rot_x(TO_RAD(90.0));

	uv = in_uv;
	vertex_pos = in_position;
	norm = (model * vec4(in_normal, 1.0)).xyz;

	vec3 T = normalize(vec3(model * vec4(in_tangent,   0)));
	vec3 B = normalize(vec3(model * vec4(in_bitangent, 0)));
	vec3 N = normalize(vec3(model * vec4(in_normal,    0)));
	TBN = mat3(T, B, N);

	vec4 world_space = model * vec4(in_position, 1);
	world_space_pos = world_space.xyz;

	vec4 pos = view_proj * world_space;
	gl_Position = pos;
}
