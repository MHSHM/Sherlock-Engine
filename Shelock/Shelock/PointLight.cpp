
#include "PointLight.h"
#include "Actor.h"
#include "Transform.h"

PointLight::PointLight(Actor* _owner):
	Component(_owner),
	color(glm::vec3(21.47, 23.31, 20.79)),
	radius(1.0f),
	linear(0.22),
	quadratic(0.20),
	falloff_distance(20.0f)
{
}

void PointLight::Update(float delta_time)
{
	Transform* transform = owner->Get_Component<Transform>();
	position = transform->position;
}
