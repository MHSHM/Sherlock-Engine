#pragma once

#include "Component.h"
#include "../Dependencies/GLM/vec3.hpp"

class SpotLight : public Component
{
public:
	SpotLight(class Actor* _owner); 

	void Update(float delta_time) override; 
	
	glm::vec3 position; 
	glm::vec3 forward; 
	glm::vec3 color; 

	float u;
	float p;
};

