#include "Model.h"

Model::Model(Actor* _owner):
	Component(_owner)
{

}

Model::~Model()
{
	for (auto& mesh : meshes) 
	{
		mesh.VAO.Clear(); 
	}
}
