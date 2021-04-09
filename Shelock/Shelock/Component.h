#pragma once

class Component
{
public:
	Component(class Actor* _owner); 

	virtual void Update(float delta_time); 

	virtual ~Component() {};

	inline bool operator==(const Component& other) 
	{
		return (this == &other);
	}

	class Actor* owner; 

};

