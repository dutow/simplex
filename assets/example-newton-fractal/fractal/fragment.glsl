
// Based on http://www.infinityk.com/asier/portfolio/newton-fractal-using-glsl/

#version 330 core

out vec3 color;

// TODO: make it a uniform parameter
const int max_iters = 16;

const float tolerance = 1e-8;

const int disk_radius = 10;

uniform vec2 roots[16];
uniform vec3 colors[16];
uniform int  no_roots;

#define square_lenght(a) dot((a),(a))

vec2 c_inv(vec2 c){
	float sl = dot(c,c);
	return vec2(c.x / sl, -c.y / sl);
}

vec2 c_mul(vec2 a, vec2 b){
	vec4 t = a.xyxy * b.xyyx;
	return vec2(t.x - t.y, t.z + t.w);
}

// HSV convertions from SO: http://gamedev.stackexchange.com/questions/59797/glsl-shader-change-hue-saturation-brightness
vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec2 p = gl_FragCoord.xy;
	// white near the roots
	for(int i=0;i<no_roots;++i) {
		if (distance(p, roots[i]) < disk_radius) {
			color = vec3(1,1,1);
			return;
		}
	}
	
	vec2 r[16];
    for(int i=0;i<no_roots;++i) {
		r[i] = p - roots[i];
	}

	vec2 prev_p = p;
	vec2 p_diff;
	vec2 min_distance;

	int near_root = -1;

	int it;
	for (it=0;it<max_iters;++it) {
		prev_p = p;
		p_diff = vec2(0,0);
		for(int i=0;i<no_roots;++i) {
			p_diff += c_inv(r[i]);
		}
		p -= c_inv( p_diff );

		for(int i=0;i<no_roots;++i) {
			r[i] = p - roots[i];
			if (square_lenght(r[i]) < tolerance) { 
				near_root = i;
				break;
			}
		}
		if (near_root != -1) {
			break;
		}
	}

	if (near_root == -1) {
		color = vec3(0,0,0);
		return;
	}

	vec3 hsv = rgb2hsv(colors[near_root]);
	hsv.z *= float(max_iters-it+2)/float(max_iters+2);

	color = hsv2rgb(hsv);
	


}