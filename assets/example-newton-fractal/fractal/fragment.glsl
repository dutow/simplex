#version 330 core
out vec3 color;
void main()
{
if(gl_FragCoord.x > 100) {
    color = vec3(1,0,0);
} else {
    color = vec3(0,1,0);
}
}