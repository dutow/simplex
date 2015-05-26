
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
	float tx_norm = 0.3 + (tx.a / 256) * 0.7 * normal.y;

	vec3 surfaceToCamera = normalize(cameraPosition - eye.xyz).xyz;
	vec3 linearColor = vec3(0);
	for(int i = 0; i < numLights; ++i){
		linearColor += ApplyLight(allLights[i], vec3(tx_norm, tx_norm, tx_norm), normal.xyz, eye.xyz, surfaceToCamera);
	}
	color.xyz = linearColor;
}

