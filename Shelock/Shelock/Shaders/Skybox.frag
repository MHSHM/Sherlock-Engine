#version 330 core

uniform samplerCube skybox; 

in vec3 o_tex_coord; 

out vec4 FragColor; 

void main()
{
	FragColor = texture(skybox, o_tex_coord); 
}