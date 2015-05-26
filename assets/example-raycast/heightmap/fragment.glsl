
#version 420 core

out vec3 color;

in vec4 eye;
in vec4 vert;
in vec2 texcoord;

uniform sampler2D terrain;


uniform vec3 cameraPosition;

#include "/common/lighting/fragment.glsl"

void main()
{
	vec4 tx = texture(terrain, texcoord);

	vec3 normal = tx.xyz;

	vec3 surfaceToCamera = normalize(cameraPosition - eye.xyz).xyz;
	vec3 linearColor = vec3(0);
	for(int i = 0; i < numLights; ++i){
		linearColor += ApplyLight(allLights[i], color.rgb, normal.xyz, eye.xyz, surfaceToCamera);
	}
	color.xyz = linearColor;
	color.xy = texcoord*2;
}

