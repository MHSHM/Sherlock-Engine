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
	class Camera* Get_Camera_Component() { return camera_component; }
	class Movement* Get_Movement_Component() { return move_component; }
	class Game* Get_Game() { return game; }


	void Set_Transform(class Transform* transform) { transform_component = transform;  }

	~Actor();

private:

	class Transform* transform_component; 
	class Model* model_Component; 
	class Camera* camera_component; 
	class Movement* move_component; 

	class Game* game; 

};