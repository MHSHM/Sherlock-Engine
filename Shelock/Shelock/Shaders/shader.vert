#version 330 core

layout (location = 0) in vec3 u_Position;
layout (location = 1) in vec3 u_normal; 
layout (location = 2) in vec2 u_uvcoord; 
  
uniform mat4 u_world_matrix; 
uniform mat4 u_view_matrix; 
uniform mat4 u_projection_matrix;

void main()
{
    gl_Position = u_projection_matrix * u_view_matrix * u_world_matrix * vec4(u_Position, 1.0f); 
}