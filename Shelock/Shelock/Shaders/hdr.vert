#version 330 core 

layout (location = 0) in vec3 u_position;
layout (location = 1) in vec2 u_uvcoord; 

out vec2 o_uvcoord; 

void main()
{
	gl_Position = vec4(u_position, 1.0f); 
	o_uvcoord = u_uvcoord; 
}
