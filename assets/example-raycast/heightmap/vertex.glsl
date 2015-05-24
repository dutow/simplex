#version 330 core
layout(location = 0) in vec2 vertexPosition_modelspace;

uniform mat4 camera;
uniform mat4 view;

uniform sampler2D terrain;

float length = 100.0f;

out vec2 texcoord;
out vec4 eye;
void main(){
  texcoord = vertexPosition_modelspace.xy / length;
  gl_Position.xz = vertexPosition_modelspace;
  gl_Position.y = texture(terrain, texcoord).x * 10.0f;
  gl_Position.w   = 1.0f;
  
  eye.xz = vertexPosition_modelspace / length;
  eye.y = texture(terrain, texcoord).x * 10.0f;
  eye.w = 1;
  eye = -(view * eye);
 
  gl_Position = camera * gl_Position;

}