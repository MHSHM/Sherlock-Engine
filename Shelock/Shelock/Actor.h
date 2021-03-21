#pragma once

#include "Transform.h"

class Actor
{
public:

	Actor();

	virtual void Process_Input();
	void Update(float delta_time); 

	Transform& Get_Transform() { return transform_component;  }

	virtual ~Actor() {};

protected:
	Transform transform_component;
};

