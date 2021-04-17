#pragma once

#include "Actor.h"
#include "Transform.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Movement.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"


#include <vector>

#define MAX_COMPONENTS 50

template<class T>
class ComponentManager
{
public:

	void Init() 
	{
		components.reserve(MAX_COMPONENTS); 
	}

	void Add_Component(class Actor* owner)
	{
		T cmp(owner); 
		components.push_back(std::move(cmp));
		owner->components.push_back(&components.back());
	}

	void Remove_Component(class Actor* owner, T* component)
	{

		if (!component) return; 



		// we remove the component from the game using swap with back trick
		// we still need to adjust the the pointer that the owner has for the back
		// as after swapping the pointer will be pointing to wrong component
		std::vector<Component*>& back_owner_components = components.back().owner->components;
		auto iter1 = std::find(back_owner_components.begin(), back_owner_components.end(), components.back().owner->Get_Component<T>());
		if(iter1 != back_owner_components.end())
		{
			std::iter_swap(iter1, back_owner_components.end() - 1);
			back_owner_components.pop_back();
		}

		auto iter2 = std::find(components.begin(), components.end(), *component);
		if (iter2 != components.end()) 
		{
			back_owner_components.push_back(&(*iter2));
			std::iter_swap(iter2, components.end() - 1);
			components.pop_back();
		}

		// remove pointer
		auto iter3 = std::find(owner->components.begin(), owner->components.end(), component); 
		if (iter3 != owner->components.end()) 
		{
			std::iter_swap(iter3, owner->components.end() - 1);
			owner->components.pop_back();
		} 
	}

	std::vector<T> components; 

};

