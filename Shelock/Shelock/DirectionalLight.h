#pragma once

#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"

class DirectionalLight : public Component
{
public:
	
	DirectionalLight(class Actor* _owner); 

	void Update(float delta_time) override;

	glm::vec3 direction; 
	glm::vec3 color; 
};

