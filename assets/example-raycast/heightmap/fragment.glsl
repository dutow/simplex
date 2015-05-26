
#version 420 core

out vec3 color;

in vec4 eye;
in vec4 vert;
in vec2 texcoord;

uniform sampler2D terrain;


uniform vec3 cameraPosition;

////////////////////////////////////////////
// LIGHTING

uniform vec3 materialSpecularColor = vec3(0);
uniform float materialShininess = 0.0f;

#define MAX_LIGHTS 10
uniform int numLights;
uniform struct Light {
   vec4 position; // w=0 means directional light
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
   float coneAngle;
   vec3 coneDirection;
} allLights[MAX_LIGHTS];

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

    //linear color (color before gamma correction)
    return ambient + attenuation*(diffuse + specular);
}

/////////////////////////////////////////////

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

