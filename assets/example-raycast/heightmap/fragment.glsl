
#version 330 core

out vec3 color;

in vec2 texcoord;

uniform sampler2D terrain;

void main()
{
	color = vec3(1.0f,0.0f,0.0f) *  texture(terrain, texcoord).xyz;
	color.y = 0.3f;
}