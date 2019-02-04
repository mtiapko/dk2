#version 330 core

varying vec3 vert_uv;

uniform samplerCube skybox;

void main()
{
	gl_FragColor = texture(skybox, vert_uv);
}
