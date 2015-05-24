#version 420

// pipeline-ból bejövõ per-fragment attribútumok
vec3	 vs_out_pos;

// kimenõ érték - a fragment színe
out vec4 fs_out_col;

//
// uniform változók
//
uniform mat4 viewProj;
uniform mat4 viewIprojI;
uniform mat4 modelI;
uniform mat4 model;
uniform mat4 view;

// objects are ALWAYS centered at 0,0,0
uniform vec3 center = vec3(0,0,0);
uniform vec3 cameraPosition;
uniform vec3 screen_size;
uniform int object_type;

uniform float INC = 1/16.0f;

////////////////////////////////////////////
// LIGHTING

uniform vec3 materialSpecularColor = vec3(1);
uniform float materialShininess = 0.3f;

#define MAX_LIGHTS 10
uniform int numLights = 0;
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

const float epsilon = 0.0001;

void getRay(in vec3 inVec, out vec3 rayOrig, out vec3 rayDir)
{
	// a világKR-ben a kattintásnak a közeli vágósíkon megfeleltetett pont koordinátái
	vec4 nearPt = viewIprojI * vec4(inVec.xy,-1, 1);
	// a világKR-ben a kattintásnak a távoli vágósíkon megfeleltetett pont koordinátái
	vec4 farPt  = viewIprojI * vec4(inVec.xy, 1, 1);

	// induljon a sugár a közeli vágosíkról
	rayOrig = nearPt.xyz/nearPt.w;

	// a sugár iránya innen trivi
	vec3 rayEnd = farPt.xyz/farPt.w;
	rayDir  = normalize( rayEnd - rayOrig  );
}

float obj_cube(vec3 p) // ^1
{
	vec3 d = abs(p) - 1;
	return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

float obj_triprism(vec3 p) // ^1
{
	vec3 h = vec3(1,1,1);
	vec3 q = abs(p);
    return max(q.z-h.y,max(q.x*0.866025+p.y*0.5,-p.y)-h.x*0.5);
}


float obj_sphere(vec3 p) // ^2
{
	return length(p) - 1;
}

float obj_torus(vec3 p) // ^2
{
	vec2 t = vec2(1,0.3);
	vec2 q = vec2(length(p.xy)-t.x,p.z);
    return length(q)-t.y;
}

float obj_hunt1(vec3 p) // ^3
{
	if (length(p) > 2) return 1;
/*	float pa = p.x*p.z;
	float pb = p.x+p.z;
	float pc = p.y*p.y - p.x*p.x;
	return pa+pb*pc;*/
	
	return p.x * p.z + p.y*p.y*p.z + pow(p.x,3);
}

float obj_hunt2(vec3 p) // ^3
{
	if (length(p) > 2) return 1;
	return p.x * p.z + pow(p.y,3);
}

// higher order length functions

float length2( vec2 p )
{
	return sqrt( p.x*p.x + p.y*p.y );
}

float length8( vec2 p )
{
	p = p*p; p = p*p; p = p*p;
	return pow( p.x + p.y, 1.0/8.0 );
}

float length4v3( vec3 p )
{
	p = p*p; p = p*p;
	return pow( p.x + p.y + p.z, 1.0/4.0 );
}

float obj_torus82( vec3 p ) // ^8 (length)
{
  vec2 t = vec2(1,0.3);
  vec2 q = vec2(length2(p.xz)-t.x,p.y);
  return length8(q)-t.y;
}

float obj_torus88( vec3 p) // ^8 (length)
{
  vec2 t = vec2(1,0.3);
  vec2 q = vec2(length8(p.xz)-t.x,p.y);
  return length8(q)-t.y;
}

float obj_sphere4(vec3 p) // ^4 - alias rounded box
{
	return length4v3(p) - 1;
}

// operators

float opU( float d1, float d2 ) // union
{
    return min(d1,d2);
}

float opS( float d1, float d2 ) // substract
{
    return max(-d1,d2);
}

float opI( float d1, float d2 ) // intersection
{
    return max(d1,d2);
}

float obj_csgtest(vec3 p) // halmazmuvelet teszt
{
	return opU(obj_torus(p), opS(obj_triprism(p), opI(obj_sphere(p), obj_torus88(p))));
}


float obj_curr(vec3 p) {
	if (object_type == 1) { // SPHERE ^2
		return obj_sphere(p);
	}
	if (object_type == 2) { // TORUS ^2
		return obj_torus(p);
	}
	if (object_type == 3) { // CUBE ^1
		return obj_cube(p);
	}
	if (object_type == 4) { // TORUS82 ^8
		return obj_torus82(p);
	}
	if (object_type == 5) { // HUNT1 ^3
		return obj_hunt1(p);
	}
	if (object_type == 6) { // HUNT2 ^3
		return obj_hunt2(p);
	}
	if (object_type == 7) { // TRIPRISM ^1
		return obj_triprism(p);
	}
	if (object_type == 8) { // TORUS88 ^8
		return obj_torus88(p);
	}
	if (object_type == 9) { // SPHERE4 ^4
		return obj_sphere4(p);
	}
	if (object_type == 10) { // CSG_TEST
		return obj_csgtest(p);
	}
}

vec3 rm_normal(vec3 point)
{
	vec3 eps = vec3( 0.001, 0.0, 0.0 );
	
    vec3 nor = vec3(
	    obj_curr(point+eps.xyy).x - obj_curr(point-eps.xyy).x,
	    obj_curr(point+eps.yxy).x - obj_curr(point-eps.yxy).x,
	    obj_curr(point+eps.yyx).x - obj_curr(point-eps.yyx).x );
	return nor;
}


void main()
{
	//fs_out_col = vec4(1,1,1,1);
	int steps = 70;
	vec3 rayOrig, rayDir;

	vs_out_pos.x = (gl_FragCoord.x / screen_size.x) *2 -1;
	vs_out_pos.y = (gl_FragCoord.y / screen_size.y) *2 -1;
	
	getRay(vs_out_pos, rayOrig, rayDir);

	rayOrig = (modelI * vec4(rayOrig, 1) ).xyz;
	rayDir  = (modelI * vec4(rayDir,  0) ).xyz;
	
	// raymarch - scene is around 120x120
	
	float t = 0;
	while ( obj_curr( rayOrig + t*rayDir ) > 0 && t < steps )
	{
		t += INC;
	}

	// ha tul messze van
	if ( t >= steps ) {
		discard;
	}

	// ha mogottunk van a metszespont, akkor dobjuk el a fragmentet
	if ( t < 0 ) {
		discard;
	}

	// különben számítsuk ki a metszéspontot
	vec3 intersectionPoint = rayOrig + t*rayDir;
	
	vec3 surfaceNormal = rm_normal(intersectionPoint);

	intersectionPoint = (model * vec4(intersectionPoint, 1) ).xyz;
	surfaceNormal = normalize( ( model * vec4(surfaceNormal, 0) ).xyz);

	// FENYHEZ
	// surfaceNormal - normalvektor, modelspace
	// intersectionPoint - felszin, modelspace
	// 
	
	vec3 surfaceToCamera = normalize(cameraPosition - intersectionPoint);
	vec3 linearColor = vec3(0);
	for(int i = 0; i < numLights; ++i){
		vec3 surfaceColor = vec3(0.6); // TODO
		linearColor += ApplyLight(allLights[i], surfaceColor.rgb, surfaceNormal, intersectionPoint, surfaceToCamera);
	}
	fs_out_col.xyz = linearColor;

	// viewport transzformáció: http://www.songho.ca/opengl/gl_transform.html 
	// gl_DepthRange: http://www.opengl.org/registry/doc/GLSLangSpec.4.30.6.pdf , 130.o. 
	vec4 clipPos = viewProj * vec4( intersectionPoint, 1 );

	float zndc = clipPos.z / clipPos.w; 

	float n = gl_DepthRange.near;
	float f = gl_DepthRange.far;

	gl_FragDepth = (f-n)/2 * zndc + (f+n)/2;
}