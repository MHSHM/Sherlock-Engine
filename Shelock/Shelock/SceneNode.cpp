#include "Scene.h"

SceneNode::SceneNode(Scene* _scene):
	actor(nullptr),
	parent(nullptr),
	scene(_scene)
{
	children.reserve(MAX_CHILDREN); 
	scene->scene_actors.emplace_back(Actor(scene->game)); 
	actor = &(scene->scene_actors.back()); 
}

void SceneNode::Add_Child(SceneNode* child)
{
	child->parent = this; 
	children.emplace_back(child); 
}

void SceneNode::Remove_Child(SceneNode* child)
{
	child->parent = nullptr;
	scene->Remove_Scene_Node(child); 
}