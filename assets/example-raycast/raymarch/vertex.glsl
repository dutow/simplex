#version 150

// VBO-b�l �rkez� v�ltoz�k
in vec2 vs_in_pos;

// a pipeline-ban tov�bb adand� �rt�kek
out vec3 vs_out_pos;

void main()
{
	gl_Position = vec4( vs_in_pos, 1, 1 );
	vs_out_pos.z = 0.0f;
	vs_out_pos.xy = vs_in_pos;
}