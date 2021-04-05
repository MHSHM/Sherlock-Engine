#version 330 core


struct Point_Light 
{
    vec3 position; 
    vec3 color; 
    float radius;
    float linear; 
	float quadratic; 
    float falloff_distance; 
};

struct Spot_Light 
{
    float u; 
    float p; 
    vec3 position; 
    vec3 forward; 
    vec3 color; 
};

in vec3 o_normal; 
in vec3 o_position; 

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 