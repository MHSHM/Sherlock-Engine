#pragma once

#include "Component.h"

#include <vector>
#include <unordered_map>


class Actor
{
public:

	Actor(class Game* _game);
	
	void Clear(); 

	inline bool operator==(const Actor& other)
	{
		return (this == &other); 
	}

	template<class T>
	T* Get_Component();

	std::vector<class Component*> components; 


	class Game* game; 

};

template<class T>
T* Actor::Get_Component()
{
	for (int i = 0; i < components.size(); ++i)
	{
		T* t = dynamic_cast<T*>(components[i]);
		if (t != nullptr)
		{
			return t;
		}
	}
	return nullptr;
}