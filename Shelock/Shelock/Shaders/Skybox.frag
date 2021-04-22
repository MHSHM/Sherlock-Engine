#version 330 core

uniform samplerCube skybox; 

in vec3 o_tex_coord; 

out vec4 FragColor; 

void main()
{
	float gamma = 2.2f;
	
	vec3 color = texture(skybox, o_tex_coord).rgb;
	color = pow(color, vec3(gamma)); 
	
	FragColor = vec4(color, 1.0f); 
}