#pragma once

#include <vector>

class Actor
{
public:

	Actor();

	void Add_Component(class Component* cmp);
	void Remove_Component(class Component* cmp); 

	template<class T>
	T* Get_Component(); 

	void Update(float delta_time);

	~Actor();

private:
	std::vector<class Component*> components; 
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
