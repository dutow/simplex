#version 150

// VBO-ból érkezõ változók
in vec3 vs_in_pos;

// a pipeline-ban tovább adandó értékek
//out vec3 vs_out_pos;

uniform mat4 viewProj;
uniform mat4 model;

void main()
{
	gl_Position = viewProj * model * vec4( vs_in_pos, 1 );
	//gl_Position.z = 0.0f;
	//gl_Position.xy = gl_Position.xy / gl_Position.w;
	//gl_Position.w = 1;
	
	//vs_out_pos.z = 0.0f;
	//vs_out_pos.xy = gl_Position.xy;
	
}