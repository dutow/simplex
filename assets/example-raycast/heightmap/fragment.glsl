
#version 330 core

out vec3 color;

in vec2 texcoord;

uniform sampler2D terrain;

uniform vec3 sun_direction;
uniform vec3 sun_color;
uniform float sun_intensity;

void main()
{
	float s11 = texture(terrain, texcoord).x;
	color = vec3(1.0f,0.0f,0.0f) *  s11;
	color.y = 0.3f;

	// calculate normal
	float NORMAL_OFF = (1.0 / 2048.0);
	vec3 off = vec3(-NORMAL_OFF, 0, NORMAL_OFF);
	float s01 = texture2D(terrain, vec2(texcoord.xy + off.xy)).x;
	float s21 = texture2D(terrain, vec2(texcoord.xy + off.zy)).x;
	float s10 = texture2D(terrain, vec2(texcoord.xy + off.yx)).x;
	float s12 = texture2D(terrain, vec2(texcoord.xy + off.yz)).x;
	vec3 va = normalize( vec3(off.z, 0.0, s21 - s11) );
	vec3 vb = normalize( vec3(0.0, off.z, s12 - s11) );
	vec3 v_normal = normalize( cross(va, vb) );

	float diffuse_intensity = max(0.0, dot(normalize(v_normal), -sun_direction)); 

	color = color * sun_color * (sun_intensity+diffuse_intensity); 
}