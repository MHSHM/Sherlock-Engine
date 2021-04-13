#version 330 core

layout (location = 0) in vec3 u_position;
layout (location = 1) in vec3 u_normal; 
layout (location = 2) in vec2 u_uvcoord; 
  
uniform mat4 u_world_matrix; 
uniform mat4 u_view_matrix; 
uniform mat4 u_projection_matrix;

out vec3 o_normal; 
out vec3 o_position; 
out vec2 o_uvcoord; 

void main()
{
    gl_Position = u_projection_matrix * u_view_matrix * u_world_matrix * vec4(u_position, 1.0f);
    o_normal = vec3(u_world_matrix * vec4(u_normal, 0.0f));
    o_position = vec3(u_world_matrix * vec4(u_position, 1.0f));
    o_uvcoord = u_uvcoord; 
}