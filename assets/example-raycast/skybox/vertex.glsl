#version 330 core

layout(location = 0) in vec2 vertexPosition_modelspace;

uniform mat4 projection;

smooth out vec3 eyeDirection;

void main(){
  vec4 aPosition;
  aPosition.xy = vertexPosition_modelspace;
  aPosition.z = 1.0f;
  aPosition.w = 1.0f;

  mat4 inverseProjection = inverse(projection);

  eyeDirection = (inverseProjection * aPosition).xyz;
  
  gl_Position = aPosition;
}