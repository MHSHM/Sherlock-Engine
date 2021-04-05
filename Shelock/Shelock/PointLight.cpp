
#include "PointLight.h"
#include "Actor.h"
#include "Transform.h"

PointLight::PointLight(Actor* _owner):
	Component(_owner),
	color(glm::vec3(1.0f, 1.0f, 1.0f)),
	radius(1.0f),
	linear(0.22),
	quadratic(0.20),
	falloff_distance(20.0f)
{
}

void PointLight::Update(float delta_time)
{
	position = owner->Get_Transform_component()->Get_Position();
}
