#include "Component.h"
#include "Actor.h"

Component::Component(Actor* _owner):
	owner(_owner)
{
	owner->Add_Component(this);
}

void Component::Update(float delta_time)
{

}
