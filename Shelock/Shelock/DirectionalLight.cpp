#include "DirectionalLight.h"
#include "Actor.h"
#include "Transform.h"

DirectionalLight::DirectionalLight(Actor* _owner):
	Component(_owner),
	color(1.0f, 1.0f, 1.0f)
{
}

void DirectionalLight::Update(float delta_time)
{
	direction = glm::normalize(owner->Get_Component<Transform>()->position); 
}
