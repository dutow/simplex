
#version 330 core

out vec4 color;

uniform samplerCube texUnit;

smooth in vec3 eyeDirection;


void main()
{
	color = texture(texUnit, eyeDirection);
}