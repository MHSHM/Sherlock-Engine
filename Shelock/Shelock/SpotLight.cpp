#include "SpotLight.h"
#include "Actor.h"
#include "Transform.h"

SpotLight::SpotLight(Actor* _owner):
	Component(_owner),
	u(0.82f),
	p(0.62f),
	color(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

void SpotLight::Update(float delta_time) 
{
	position = owner->Get_Transform_component()->Get_Position(); 
	forward = owner->Get_Transform_component()->Get_Forward(); 
}