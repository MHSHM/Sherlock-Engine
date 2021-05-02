#include "DirectionalLight.h"
#include "Actor.h"
#include "Transform.h"

DirectionalLight::DirectionalLight(Actor* _owner):
	Component(_owner),
	color(50.47, 50.31, 50.79)
{
}

void DirectionalLight::Update(float delta_time)
{
	direction = glm::normalize(owner->Get_Component<Transform>()->position); 
}
