#include "SceneNode.h"
#include "Actor.h"

SceneNode::SceneNode(Scene& scene):
	actor(nullptr),
	parent(nullptr)
{
	actor = new Actor; 
	scene.Add_Scene_Node(this); 
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
	delete actor; 
}
