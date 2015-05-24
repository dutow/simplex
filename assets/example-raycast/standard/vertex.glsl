#version 330 core
layout(location = 0) in vec3 vp_modelspace;
layout(location = 1) in vec3 vp_normal;
layout(location = 2) in vec2 vp_texcoord;

uniform mat4 camera;
uniform mat4 model;

out vec4 normal;
out vec2 texcoord;

void main(){
  vec4 position;
  position.xyz = vp_modelspace;
  position.w   = 1.0f;
  position = camera * model * position;

  normal.xyz = vp_normal;
  normal.w   = 1.0f;
  normal = normalize(camera * model * normal);
  
  texcoord = vp_texcoord;
  
  gl_Position = position;
}