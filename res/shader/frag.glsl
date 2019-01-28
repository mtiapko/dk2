#version 330 core

varying vec3 vert_norm;
varying vec2 vert_uv;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, vec2(vert_uv.x, 1.0 - vert_uv.y));
	//FragColor = vec4(vec3(0.4), 1.0);
}
