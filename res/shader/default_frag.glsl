#version 330 core
precision mediump float;

uniform sampler2D DK_DIFFUSE_TEX;
uniform sampler2D DK_SPECULAR_TEX;
uniform sampler2D DK_NORMAL_TEX;
//uniform float uni_diff_val;

uniform vec3 camera_pos;
uniform float kek;
in vec2 uv;
in vec3 vertex_pos;
in mat3 TBN;
in vec3 norm;
out vec4 FragColor;

const vec3 light_dir = normalize(vec3(0, -1, -5));
//vec3 light_dir = normalize(camera_pos);

#if 1
void main()
{
	vec4 diffuse_color = texture2D(DK_DIFFUSE_TEX, vec2(uv.x, 1.0 - uv.y));
	vec3 normal_color = norm;//normalize(TBN * normalize(texture2D(DK_NORMAL_TEX, vec2(uv.x, 1.0 - uv.y)).rgb * 2.0 - 1.0));
	vec3 specular_color = texture2D(DK_SPECULAR_TEX, vec2(uv.x, 1.0 - uv.y)).rgb;

	/* diffuse */
	float diff = max(dot(normal_color, -light_dir), 0.175);

	vec3 diffuse = diff * diffuse_color.rgb;

	/* specular */
	const float shininess = 8.0;
	// TODO: camera pos to world space
	vec3 camera_dir = normalize(camera_pos - vertex_pos);
	vec3 reflect_dir = reflect(-light_dir, normal_color);
	float spec = pow(max(dot(camera_dir, reflect_dir), 0.0), shininess);
	vec3 specular = spec * specular_color;

	if (kek < 0.5)
		FragColor = vec4(diffuse + specular, diffuse_color.a);
	else
		FragColor = vec4(norm, 1.0);
}
#else

uniform vec3 material_color;

void main()
{
	float diff = max(dot(norm, -light_dir), 0.0);
	vec3 diffuse = diff * material_color;
	vec3 color = diffuse + vec3(0.165);
	if (kek < 0.5)
		FragColor = vec4(color, 1);
	else
		FragColor = vec4(norm, 1);
}

#endif
