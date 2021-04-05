#pragma once

#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"

class PointLight : public Component
{
public:
	PointLight(class Actor* _owner);

	void Update(float delta_time) override;

	glm::vec3& Get_Position() { return position; }
	glm::vec3& Get_Color() { return color; }
	float& Get_Radius() { return radius; }
	float& Get_Linear_Term() { return linear; }
	float& Get_Quadratic_Term() { return quadratic; }
	float& Get_Falloff_Distance() { return falloff_distance; }

private:
	glm::vec3 position; 
	glm::vec3 color; 
	float radius;
	float linear; 
	float quadratic; 
	float falloff_distance;
};

