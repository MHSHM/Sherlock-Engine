#pragma once


#include "Component.h"
#include "Mesh.h"

#include <vector>

class Model : public Component
{
public:
	Model(class Actor* _owner); 
	~Model(); 

	std::vector<Mesh> meshes; 
};

