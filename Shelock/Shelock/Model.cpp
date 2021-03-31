#include "Model.h"

Model::Model(Actor* _owner):
	Component(_owner)
{

}

Model::~Model()
{
	for (auto& mesh : meshes) 
	{
		mesh.Get_VAO().Clear(); 
	}
}
