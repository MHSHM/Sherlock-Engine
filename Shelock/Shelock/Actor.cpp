#include "Actor.h"
#include "Transform.h"

Actor::Actor()
{
}

void Actor::Add_Component(Component* cmp)
{
	components.emplace_back(cmp); 
}

void Actor::Remove_Component(Component* cmp)
{
	auto iter = std::find(components.begin(), components.end(), cmp);
	if (iter != components.end()) 
	{
		delete* iter; 
		components.erase(iter); 
	}
}

void Actor::Update(float delta_time)
{
	for (int i = 0; i < components.size(); ++i) 
	{
		components[i]->Update(delta_time); 
	}
}

Actor::~Actor()
{
	for (int i = 0; i < components.size(); ++i) 
	{
		Remove_Component(components[i]); 
	}
}
