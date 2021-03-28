#pragma once

#include "Component.h"

#include <vector>

class Actor
{
public:

	Actor(class Game* _game);

	void Add_Component(const ComponentType& type);
	void Remove_Component(const ComponentType& type);

	inline bool operator==(const Actor& other)
	{
		return (this == &other); 
	}

	class Transform* Get_Transform_component() { return transform_component;  }
	class Model* Get_Model_Component() { return model_Component;  }

	void Set_Transform(class Transform* transform) { transform_component = transform;  }

	~Actor();

private:

	class Transform* transform_component; 
	class Model* model_Component; 
	
	class Game* game; 

};