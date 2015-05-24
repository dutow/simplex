#version 130

// pipeline-b�l bej�v� per-fragment attrib�tumok
in vec3 vs_out_pos;

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

uniform vec3 center = vec3(0,0,0);
uniform float r = 1;

uniform vec3 lightPos = vec3(0,20,0);

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

void main()
{
	vec3 rayOrig, rayDir;

	getRay(vs_out_pos, rayOrig, rayDir);

	rayOrig = (modelI * vec4(rayOrig, 1) ).xyz;
	rayDir  = (modelI * vec4(rayDir,  0) ).xyz;

	// masodfoku egyenlet eh-i
	float A = dot(rayDir,rayDir); // kell ez?
	float B = 2*dot(rayDir, rayOrig - center);
	float C = dot( rayOrig - center, rayOrig - center) - r*r;

	// oldjuk is meg
	float discr = B*B - 4*A*C;

	if ( discr < 0)
	{
		// nincs mp
		discard;
	}

	// gyokok
	float t1 = (-B - sqrt(discr))/(2*A);
	float t2 = (-B + sqrt(discr))/(2*A);

	float t = t1;

	if ( t1 < 0 )
		t = t2;

	// ha mogottunk van a metszespont, akkor dobjuk el a fragmentet
	if ( t < 0 )
		discard;

	// k�l�nben sz�m�tsuk ki a metsz�spontot
	vec3 intersectionPoint = rayOrig + t*rayDir;
	vec3 surfaceNormal = normalize(intersectionPoint - center);

	intersectionPoint = (model * vec4(intersectionPoint, 1) ).xyz;
	surfaceNormal = normalize( ( model * vec4(surfaceNormal, 0) ).xyz);

	// egyszeru diffuz szin
	vec3 toLight = normalize(lightPos - intersectionPoint);
	vec4 diffuseColor = vec4(clamp( dot(surfaceNormal, toLight), 0, 1 ));

	fs_out_col = diffuseColor + vec4(0.2f);

	// viewport transzform�ci�: http://www.songho.ca/opengl/gl_transform.html 
	// gl_DepthRange: http://www.opengl.org/registry/doc/GLSLangSpec.4.30.6.pdf , 130.o. 
	vec4 clipPos = viewProj * vec4( intersectionPoint, 1 );

	float zndc = clipPos.z / clipPos.w; 

	float n = gl_DepthRange.near;
	float f = gl_DepthRange.far;

	gl_FragDepth = (f-n)/2 * zndc + (f+n)/2;
}