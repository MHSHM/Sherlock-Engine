#include "SpotLight.h"
#include "Actor.h"
#include "Transform.h"

SpotLight::SpotLight(Actor* _owner):
	Component(_owner),
	u(0.82f),
	p(0.62f),
	color(glm::vec3(31.47, 33.31, 30.79))
{
}

void SpotLight::Update(float delta_time) 
{
	Transform* transform = owner->Get_Component<Transform>(); 
	position = transform->position; 
	forward = transform->forward; 
}