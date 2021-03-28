#include "Scene.h"

SceneNode::SceneNode(Scene* _scene):
	actor(nullptr),
	parent(nullptr),
	scene(_scene)
{
	children.reserve(MAX_CHILDREN); 
	scene->Get_Scene_Actors().emplace_back(Actor(scene->Get_Game())); 
	actor = &(scene->Get_Scene_Actors().back()); 
}

void SceneNode::Add_Child(SceneNode* child)
{
	child->parent = this; 
	children.emplace_back(child); 
}

void SceneNode::Remove_Child(SceneNode* child)
{
	child->parent = nullptr;
	auto iter = std::find(children.begin(), children.end(), child); 
	if (iter != children.end()) 
	{
		children.erase(iter); 
	}
}

SceneNode::~SceneNode()
{
}
