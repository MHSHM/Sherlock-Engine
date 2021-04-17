#version 330 core

layout (location = 0) in vec3 position; 

uniform mat4 u_world; 
uniform mat4 u_view; 
uniform mat4 u_projection;

out vec3 o_tex_coord;

void main()
{
	vec3 view_pos = vec3(u_view * vec4(position, 0.0f)); 
	gl_Position = u_projection * vec4(view_pos, 1.0f);
	o_tex_coord = position; 
}  