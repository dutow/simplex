#version 330 core

out vec3 color;

uniform vec4 computed_parts[16];
uniform vec2 roots[16];
uniform int  no_roots;

void main()
{
    // white near the roots

	for(int i=0;i<no_roots;++i) {
		if (distance(vec2(gl_FragCoord.x, gl_FragCoord.y), roots[i]) < 20) {
			color = vec3(1,1,1);
			return;
		}
	}

if(no_roots > 1) {
    color = vec3(1,0,0);
} else {
    color = vec3(0,1,0);
}
}