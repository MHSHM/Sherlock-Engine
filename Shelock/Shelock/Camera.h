#pragma once
#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"
#include "../Dependencies/GLM/mat4x4.hpp"
#include "../Dependencies/GLM/gtc/matrix_transform.hpp"
#include "../Dependencies/GLM/gtx/transform.hpp"

class Camera : public Component
{
public:
	Camera(class Actor* _owner);

	void Update(float delta_time) override; 

	glm::mat4& Get_View() { return view; }
	glm::mat4& Get_Projection() { return projection; }

private:
	float near_plane; 
	float far_plane;

	// in degrees
	float field_of_view;

	glm::mat4 view; 
	glm::mat4 projection; 

	glm::vec3 camera_forward; 
	glm::vec3 camera_up; 
	glm::vec3 camera_right; 
};

