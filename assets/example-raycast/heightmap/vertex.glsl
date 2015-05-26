#version 420 core

in vec2 vp;

uniform mat4 camera;
uniform mat4 view;

uniform sampler2D terrain;

out vec2 texcoord;
out vec4 eye;
out vec4 vert;

void main(){
  texcoord.x = vp.x / 512.0;
  texcoord.y = vp.y / 512.0;
  vec4 v = vec4(vp.x, texture(terrain, texcoord).a, vp.y, 1.0);
  
  gl_Position = v;
  eye = -(view * v);
  vert = v;
  gl_Position = camera * gl_Position;

}