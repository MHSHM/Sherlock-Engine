#version 330 core

const int MAX_POINT_LIGHT = 10; 
const int MAX_SPOT_LIGHT = 10; 

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

struct Material 
{
    sampler2D albedo; 
    sampler2D normals; 
};

// No. of point lights in scene; 
uniform int scene_point_lights; 
uniform Point_Light point_lights[MAX_POINT_LIGHT]; 

uniform int scene_spot_light; 
uniform Spot_Light spot_lights[MAX_SPOT_LIGHT]; 

in vec3 o_normal; 
in vec3 o_position; 
in vec2 o_uvcoord; 
in mat3 TBN; 

out vec4 FragColor;

uniform Material surface_material; 



vec3 Get_Normal()
{
    vec3 frag_normal = texture(surface_material.normals, o_uvcoord).rgb; 
    frag_normal = frag_normal * 2.0f - 1.0f; 
    frag_normal = normalize(TBN * frag_normal); 
    return frag_normal; 
}

vec3 pointlights_calculations(vec3 mapped_normal)
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f); 
    for(int i = 0; i < scene_point_lights; ++i)
    {
        vec3 light_direction = point_lights[i].position - o_position; 
        float angle = max(dot(normalize(light_direction), mapped_normal), 0.0f); 
        float d = length(light_direction); 
        float d_squared = d * d; 
        float attenution = 1.0f / (min(point_lights[i].radius, d) + (d * point_lights[i].linear) + (point_lights[i].quadratic * d_squared));
        color += angle * attenution * point_lights[i].color; 
    }

    return color; 

}

vec3 spotlights_calculations(vec3 mapped_normal)
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < scene_spot_light; ++i)
    {
        vec3 light_direction = normalize(o_position - spot_lights[i].position); 
        float angle = max(dot(-light_direction, mapped_normal), 0.0f); 
        vec3 spotlight_forward = normalize(spot_lights[i].forward); 
        float s = dot(spotlight_forward, light_direction);
        float numerator = s - spot_lights[i].u; 
        float denominator = spot_lights[i].u - spot_lights[i].p; 
        float t = clamp(numerator / denominator, 0.0f, 1.0f);
        float t_squared = t * t; 
        float t_smooth = t_squared * (3.0f - 2.0f * t); 
        color += angle * t_smooth * spot_lights[i].color; 
    }
    return color; 
}

void main()
{
    vec3 mapped_normal = Get_Normal(); 
    vec3 lighting = pointlights_calculations(mapped_normal) + spotlights_calculations(mapped_normal); 
    FragColor = texture(surface_material.albedo, o_uvcoord) * vec4(lighting, 1.0f); 
} 