#include "Scene.h"
#include "SceneNode.h"

Scene::Scene()
{

}

void Scene::Add_Scene_Node(SceneNode* node)
{
	scene_nodes.emplace_back(node); 
}

void Scene::Remove_Scene_Node(SceneNode* node)
{
	if (node->Get_Parent()) 
	{
		node->Get_Parent()->Remove_Child(node); 
	}

	for (auto child : node->Get_Children()) 
	{
		Remove_Scene_Node(child); 
	}

	auto iter = std::find(scene_nodes.begin(), scene_nodes.end(), node); 
	delete *iter;
	scene_nodes.erase(iter);
}

void Scene::Clear_Scene()
{
	for (auto& node : scene_nodes) 
	{
		delete node; 
		node = nullptr; 
	}
	scene_nodes.clear(); 
}

Scene::~Scene()
{
}
