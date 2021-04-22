#version 330 core

uniform sampler2D hdr_scene;

in vec2 o_uvcoord; 

out vec4 FragColor; 

void main()
{
	float gamma = 2.2f; 

	vec3 hdr_color = texture(hdr_scene, o_uvcoord).rgb;
	
	// RGB to luminance 
	float l_in  = hdr_color.r * 0.2126f + hdr_color.g * 0.7152f + hdr_color.b * 0.0722f;
	
	// Tone mapping
	float l_out = l_in / (1.0f + l_in);	
	vec3 ldr_color = hdr_color * (l_out / l_in);

	// Gamma correction
    ldr_color = pow(ldr_color, vec3(1.0f / gamma));
	
	/*
	float exposure = 5.0f; 
	vec3 final = vec3(1.0) - exp(-hdr_color * exposure); 
	final = pow(final, vec3(1.0f / gamma));
	*/

	FragColor = vec4(ldr_color, 1.0f);
} 