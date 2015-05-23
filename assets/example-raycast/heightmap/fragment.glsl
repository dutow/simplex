
#version 330 core

out vec3 color;

// TODO: make it a uniform parameter
const int max_iters = 16;

const float tolerance = 1e-8;

const int disk_radius = 10;


void main()
{
	color = vec3(1.0f,0.0f,0.0f);
}