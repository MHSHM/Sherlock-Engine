#pragma once


#include "Component.h"
#include "Mesh.h"

#include <vector>

class Model : public Component
{
public:
	Model(class Actor* _owner); 

	void Set_Meshes(std::vector<Mesh> _meshes) { meshes = _meshes; }

	std::vector<Mesh>& Get_Meshes() { return meshes;  }

	class Actor* Get_Owner() { return owner; }

	~Model(); 

private:
	std::vector<Mesh> meshes; 
};

