#pragma once
#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"
#include "../Dependencies/GLM/mat4x4.hpp"
#include "../Dependencies/GLM/gtc/matrix_transform.hpp"
#include "../Dependencies/GLM/gtx/transform.hpp"

class FPSCamera : public Component
{
public:
	FPSCamera(class Actor* _owner);

	void Update(float delta_time) override; 

	float near_plane; 
	float far_plane;

	// in degrees
	float field_of_view;
	float sensitivity; 
	float forward_speed; 

	glm::vec3 forward; 
	glm::vec3 up; 
	glm::vec3 right; 

	glm::mat4 view; 
	glm::mat4 projection; 
};

