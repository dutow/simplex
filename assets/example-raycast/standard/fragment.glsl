
#version 330 core

out vec4 color;

in vec4 normal;
in vec4 eye;
in vec2 texcoord;

uniform sampler2D tex_diffuse;

uniform vec3 sun_direction;
uniform vec3 sun_color;
uniform float sun_intensity;

uniform vec3 light_position;

void main()
{
	color = texture(tex_diffuse, texcoord);
	
	
	// FENYHEZ
	// normal - normalvektor, modelspace
	// intersectionPoint - felszin, modelspace
	// 
	
	vec4 point_light = vec4(0.0);
	
	vec3 light_dir = light_position.xyz - eye.xyz;
	float light_dist = length(light_dir);
	light_dir = normalize(light_dir);
	float light_diffuse = max(0.0, dot(normal.xyz, -light_dir));
	// const + lin + exp
	float light_atttotal = 0.1 + 0.05*light_dist; + 0.1 * light_dist * light_dist;
	point_light = vec4(0.65,0.65,0.5,1) * (light_diffuse + 0.2) / light_atttotal;
	//point_light = vec4(light_diffuse);
	
	// nap
	vec3 toLight = normalize(sun_direction);
	vec4 diffuseColor = vec4(clamp( dot(normal.xyz, toLight), 0, 1 ));
	diffuseColor.xyz *= sun_color;
	vec4 sun_light = vec4(0.0);
	sun_light.xyz = diffuseColor.xyz * sun_intensity;
	
	color *= max(sun_light + point_light, vec4(0.2f));
	
}