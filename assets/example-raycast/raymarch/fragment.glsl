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

uniform vec3 screen_size;

uniform vec3 sun_direction;
uniform vec3 sun_color;
uniform float sun_intensity;
uniform int object_type;


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
	//return normalize(intersectionPoint - center);
	
	float d0 = obj_curr(point);
    float dX = obj_curr(point - vec3(epsilon, 0.0, 0.0));
    float dY = obj_curr(point - vec3(0.0, epsilon, 0.0));
    float dZ = obj_curr(point - vec3(0.0, 0.0, epsilon));
    return normalize(vec3(dX-d0, dY-d0, dZ-d0));
}

uniform float INC = 1/16.0f;

uniform vec3 light_position;

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
	
	vec4 point_light = vec4(0.0);
	
	vec3 light_dir = light_position.xyz - intersectionPoint.xyz;
	float light_dist = length(light_dir);
	light_dir = normalize(light_dir);
	float light_diffuse = max(0.0, dot(surfaceNormal, -light_dir));
	// const + lin + exp
	float light_atttotal = 0.1 + 0.05*light_dist; + 0.1 * light_dist * light_dist;
	point_light = vec4(0.65,0.65,0.5,1) * (light_diffuse + 0.2) / light_atttotal;
	//point_light = vec4(light_diffuse);
	
	// nap
	vec3 toLight = normalize(sun_direction);
	vec4 diffuseColor = vec4(clamp( dot(surfaceNormal, toLight), 0, 1 ));
	diffuseColor.xyz *= sun_color;
	vec4 sun_light = vec4(0.0);
	sun_light.xyz = diffuseColor.xyz * sun_intensity;
	
	fs_out_col = max(sun_light + point_light, vec4(0.2f));

	// viewport transzformáció: http://www.songho.ca/opengl/gl_transform.html 
	// gl_DepthRange: http://www.opengl.org/registry/doc/GLSLangSpec.4.30.6.pdf , 130.o. 
	vec4 clipPos = viewProj * vec4( intersectionPoint, 1 );

	float zndc = clipPos.z / clipPos.w; 

	float n = gl_DepthRange.near;
	float f = gl_DepthRange.far;

	gl_FragDepth = (f-n)/2 * zndc + (f+n)/2;
}