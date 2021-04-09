#pragma once

#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"

class PointLight : public Component
{
public:
	PointLight(class Actor* _owner);

	void Update(float delta_time) override;

	glm::vec3 position; 
	glm::vec3 color; 
	float radius;
	float linear; 
	float quadratic; 
	float falloff_distance;
};

