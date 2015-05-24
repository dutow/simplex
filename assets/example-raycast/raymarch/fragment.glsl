#version 420

// pipeline-b�l bej�v� per-fragment attrib�tumok
in vec3	 vs_out_pos;

// kimen� �rt�k - a fragment sz�ne
out vec4 fs_out_col;

//
// uniform v�ltoz�k
//
uniform mat4 viewProj;
uniform mat4 viewIprojI;
uniform mat4 modelI;
uniform mat4 model;
uniform mat4 view;

// objects are ALWAYS centered at 0,0,0
uniform vec3 center = vec3(0,0,0);

uniform vec3 sun_direction;
uniform vec3 sun_color;
uniform float sun_intensity;
uniform int object_type;


const float epsilon = 0.001;

void getRay(in vec3 inVec, out vec3 rayOrig, out vec3 rayDir)
{
	// a vil�gKR-ben a kattint�snak a k�zeli v�g�s�kon megfeleltetett pont koordin�t�i
	vec4 nearPt = viewIprojI * vec4(inVec.xy,-1, 1);
	// a vil�gKR-ben a kattint�snak a t�voli v�g�s�kon megfeleltetett pont koordin�t�i
	vec4 farPt  = viewIprojI * vec4(inVec.xy, 1, 1);

	// induljon a sug�r a k�zeli v�gos�kr�l
	rayOrig = nearPt.xyz/nearPt.w;

	// a sug�r ir�nya innen trivi
	vec3 rayEnd = farPt.xyz/farPt.w;
	rayDir  = normalize( rayEnd - rayOrig  );
}


uniform float sphere_radius = 1;

float obj_plane(vec3 p) // ^2
{
	return p.y;
}

float obj_sphere(vec3 p) // ^2
{
	return length(p) - sphere_radius;
}

float obj_torus(vec3 p) // ^2
{
	vec2 t = vec2(1,0.3);
	vec2 q = vec2(length(p.xy)-t.x,p.z);
    return length(q)-t.y;
}

float obj_curr(vec3 p) {
	if (object_type == 1) { // SPHERE
		return obj_sphere(p);
	}
	if (object_type == 2) { // TORUS
		return obj_torus(p);
	}
	if (object_type == 3) { // PLANE
		return obj_plane(p);
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

void main()
{
	vec3 rayOrig, rayDir;

	getRay(vs_out_pos, rayOrig, rayDir);

	rayOrig = (modelI * vec4(rayOrig, 1) ).xyz;
	rayDir  = (modelI * vec4(rayDir,  0) ).xyz;

	// raymarch - scene is around 120x120
	float t = 0;
	while ( obj_curr( rayOrig + t*rayDir ) > 0 && t < 80 )
	{
		t += INC;
	}

	// ha tul messze van
	if ( t >= 80 ) {
		discard;
	}

	// ha mogottunk van a metszespont, akkor dobjuk el a fragmentet
	if ( t < 0 )
		discard;

	// k�l�nben sz�m�tsuk ki a metsz�spontot
	vec3 intersectionPoint = rayOrig + t*rayDir;
	
	vec3 surfaceNormal = rm_normal(intersectionPoint);

	intersectionPoint = (model * vec4(intersectionPoint, 1) ).xyz;
	surfaceNormal = normalize( ( model * vec4(surfaceNormal, 0) ).xyz);

	// egyszeru diffuz szin
	vec3 toLight = normalize(sun_direction);
	vec4 diffuseColor = vec4(clamp( dot(surfaceNormal, toLight), 0, 1 ));
	diffuseColor.xyz *= sun_color;

	fs_out_col += diffuseColor * sun_intensity + vec4(0.2f);

	// viewport transzform�ci�: http://www.songho.ca/opengl/gl_transform.html 
	// gl_DepthRange: http://www.opengl.org/registry/doc/GLSLangSpec.4.30.6.pdf , 130.o. 
	vec4 clipPos = viewProj * vec4( intersectionPoint, 1 );

	float zndc = clipPos.z / clipPos.w; 

	float n = gl_DepthRange.near;
	float f = gl_DepthRange.far;

	gl_FragDepth = (f-n)/2 * zndc + (f+n)/2;
}