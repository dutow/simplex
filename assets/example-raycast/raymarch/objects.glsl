
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