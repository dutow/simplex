
#version 330 core

out vec4 color;

in vec4 normal;
in vec2 texcoord;

uniform sampler2D tex_diffuse;

uniform vec3 sun_direction;
uniform vec3 sun_color;
uniform float sun_intensity;

void main()
{
	color = texture(tex_diffuse, texcoord) * 0.4;
	
	vec3 n = normalize(normal.xyz);
	float NdotL = max(dot(n,normalize(sun_direction)),0.0);
	if (NdotL > 0.0) {
		color.xyz += sun_color * sun_intensity * NdotL;
	} else {
	}
}