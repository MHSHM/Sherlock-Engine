#include "Actor.h"

Actor::Actor():
	transform_component(this)
{

}

void Actor::Process_Input()
{

}

void Actor::Update(float delta_time)
{
	transform_component.Update(delta_time);
}