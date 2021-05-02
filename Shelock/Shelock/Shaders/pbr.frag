#version 330 core

const int MAX_POINT_LIGHT = 10; 
const int MAX_SPOT_LIGHT = 10; 
const float PI = 3.14159265359;


struct Directional_Light 
{
    vec3 direction; 
    vec3 color; 
}; 

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
    sampler2D metallic; 
    sampler2D roughness; 
    sampler2D AO;
};

// No. of point lights in scene; 
uniform int scene_point_lights; 
uniform Point_Light point_lights[MAX_POINT_LIGHT]; 

uniform int scene_spot_light; 
uniform Spot_Light spot_lights[MAX_SPOT_LIGHT]; 

uniform vec3 world_camera; 
uniform Directional_Light dir_light; 

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


vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    // interpolation between white and F0
    return F0 + (vec3(1.0f) - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float DistributionGGX(vec3 normal, vec3 halfway_director, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(normal, halfway_director), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotX, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotX;
    float denom = NdotX * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 normal, vec3 view_direction, vec3 light_direction, float roughness)
{
    float NdotV = max(dot(normal, view_direction), 0.0);
    float NdotL = max(dot(normal, light_direction), 0.0);
    
    float roughness_squared = roughness * roughness; 

    float a_l = NdotL / (roughness_squared * pow(1.0f - (NdotL * NdotL), 0.5f));  
    float a_v = NdotV / (roughness_squared * pow(1.0f - (NdotV * NdotV), 0.5f));

    float A_l = (-1.0f + pow(1.0f + (1.0f / (a_l * a_l)), 0.5f)) / 2.0f; 
    float A_v = (-1.0f + pow(1.0f + (1.0f / (a_v * a_v)), 0.5f)) / 2.0f; 

    float num = NdotV * NdotL; 
    float denom = 1.0f + A_l + A_v; 
    
    return num / denom; 

    //float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    //float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    //return ggx1 * ggx2;
}

vec3 Pointlights_Calculations(vec3 mapped_normal, vec3 view_direction, float roughness, vec3 F0, float metalliness, vec3 albedo)
{
    vec3 Lo = vec3(0.0f, 0.0f, 0.0f); 
    
    for(int i = 0; i < scene_point_lights; ++i)
    {
        
        vec3 light_direction   = point_lights[i].position - o_position;
        vec3 halfway_direction = normalize(normalize(light_direction) + view_direction); 
        
        float d = length(light_direction);
        light_direction = normalize(light_direction); 

        float d_squared = d * d; 
        float attenution = 1.0f / (min(point_lights[i].radius, d) + (d * point_lights[i].linear) + (point_lights[i].quadratic * d_squared));
        vec3 radiance = point_lights[i].color * attenution; 

        // NDF: the amount of microfacets that their normal m is aligned with the halfway vector.
        // shape and size of the specular highlights.

        // G: the amount of microfacets that are not blocked by other microfacets from light and view perspective.
        
        // F: the amount of light reflected as a portion of the incident light.
        // brightness of the specular highlights.

        float NDF = DistributionGGX(mapped_normal, halfway_direction, roughness);
        float G   = GeometrySmith(mapped_normal, view_direction, light_direction, roughness); 
        vec3 F    = fresnelSchlick(max(dot(halfway_direction, view_direction), 0.0), F0);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metalliness;
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(mapped_normal, view_direction), 0.0) * max(dot(mapped_normal, light_direction), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  

        float NdotL = max(dot(mapped_normal, light_direction), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }

    return Lo; 

}

vec3 Spotlights_Calculations(vec3 mapped_normal, vec3 view_direction, float roughness, vec3 F0, float metalliness, vec3 albedo)
{
    vec3 Lo = vec3(0.0f, 0.0f, 0.0f);
    
    for(int i = 0; i < scene_spot_light; ++i)
    {

        vec3 light_direction = normalize(o_position - spot_lights[i].position); 
        vec3 halfway_direction = normalize(-light_direction + view_direction); 
        vec3 spotlight_forward = normalize(spot_lights[i].forward); 
        
        float s = dot(spotlight_forward, light_direction);
        float n = s - spot_lights[i].u; 
        float d = spot_lights[i].u - spot_lights[i].p; 
        float t = clamp(n / d, 0.0f, 1.0f);
        float t_squared = t * t; 
        float t_smooth = t_squared * (3.0f - 2.0f * t); 

        vec3 radiance = spot_lights[i].color * t_smooth; 

        float NDF = DistributionGGX(mapped_normal, halfway_direction, roughness);
        float G   = GeometrySmith(mapped_normal, view_direction, -light_direction, roughness); 
        vec3 F    = fresnelSchlick(max(dot(halfway_direction, view_direction), 0.0), F0);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metalliness;
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(mapped_normal, view_direction), 0.0) * max(dot(mapped_normal, -light_direction), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  

        float NdotL = max(dot(mapped_normal, -light_direction), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }
    
    return Lo; 
}

vec3 Directional_light_Calculations(vec3 mapped_normal, vec3 view_direction, float roughness, vec3 F0, float metalliness, vec3 albedo)
{
    vec3 Lo = vec3(0.0f, 0.0f, 0.0f); 

    vec3 light_direction   = normalize(dir_light.direction);
    vec3 halfway_direction = normalize(light_direction + view_direction); 
        
    vec3 radiance = dir_light.color; 

    float NDF = DistributionGGX(mapped_normal, halfway_direction, roughness);
    float G   = GeometrySmith(mapped_normal, view_direction, light_direction, roughness); 
    vec3 F    = fresnelSchlick(max(dot(halfway_direction, view_direction), 0.0), F0);

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metalliness;
        
    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(mapped_normal, view_direction), 0.0) * max(dot(mapped_normal, light_direction), 0.0);
    vec3 specular     = numerator / max(denominator, 0.001);  

    float NdotL = max(dot(mapped_normal, light_direction), 0.0);                
    Lo += (kD * albedo / PI + specular) * radiance * NdotL; 

    return Lo; 
}

void main()
{
    float gamma = 2.2f;
    
    vec3 mapped_normal  = Get_Normal();
    vec3 view_direction = normalize(world_camera - o_position);  
    vec3 albedo         = pow(texture(surface_material.albedo, o_uvcoord).rgb, vec3(gamma));
    float metalliness   = texture(surface_material.metallic, o_uvcoord).r; 
    float roughness     = texture(surface_material.roughness, o_uvcoord).r;
    float ao            = texture(surface_material.AO, o_uvcoord).r; 

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metalliness);

    //vec3 ambient = vec3(0.03) * albedo * ao; 
    
    vec3 final_color = Pointlights_Calculations(mapped_normal, view_direction, roughness, F0, metalliness, albedo);

    FragColor = vec4(final_color * ao, 1.0f);
} 