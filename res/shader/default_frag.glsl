#version 330 core

uniform sampler2D tex;
out vec3 color;
varying vec3 my_norm;
varying vec2 tex_coord;

void main(){
	//color = vec3(gl_FragCoord.z);
	color = texture(tex, vec2(tex_coord.x, 1.0 - tex_coord.y)).rgb;
}
