
#version 330 core

out vec4 color;

in vec4 normal;
in vec4 eye;
in vec2 texcoord;

uniform sampler2D tex_diffuse;

uniform vec3 cameraPosition;

#include "/common/lighting/fragment.glsl"

void main()
{
	color = texture(tex_diffuse, texcoord);
	
	
	// FENYHEZ
	// normal - normalvektor, modelspace
	// intersectionPoint - felszin, modelspace
	// 
	
	vec3 surfaceToCamera = normalize(cameraPosition - eye.xyz).xyz;
	vec3 linearColor = vec3(0);
	for(int i = 0; i < numLights; ++i){
		linearColor += ApplyLight(allLights[i], color.rgb, normal.xyz, eye.xyz, surfaceToCamera);
	}
	color.xyz = linearColor;
	
}