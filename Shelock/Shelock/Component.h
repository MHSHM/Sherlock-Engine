#pragma once


class Actor; 

class Component
{
public:
	Component(Actor* _owner); 

	virtual void Update(float delta_time); 

	virtual ~Component() {};

protected:
	Actor* owner; 
};

