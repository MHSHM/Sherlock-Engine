#include "Scene.h"
#include "Game.h"
#include "Camera.h"


Scene::Scene(Game* _game):
	game(_game)
{
	scene_nodes.reserve(MAX_SCENE_NODES); 
	scene_actors.reserve(MAX_SCENE_NODES); 
	scene_nodes_transforms.reserve(MAX_SCENE_NODES); 
	scene_nodes_models.reserve(MAX_SCENE_NODES); 
	scene_cameras.reserve(MAX_SCENE_NODES); 
	scene_nodes_movements.reserve(MAX_SCENE_NODES);
	scene_point_lights.reserve(MAX_SCENE_POINT_LIGHTS); 
	scene_spot_lights.reserve(MAX_SCENE_SPOT_LIGHTS); 
}

SceneNode* Scene::Add_Scene_Node(SceneNode node)
{
	scene_nodes.push_back(node); 
	return &scene_nodes.back();
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

	auto iter1 = std::find(scene_nodes.begin(), scene_nodes.end(), *node);
	auto iter2 = std::find(scene_actors.begin(), scene_actors.end(), *(node->Get_Actor())); 
	scene_nodes.erase(iter1);
	scene_actors.erase(iter2); 
}

Scene::~Scene()
{
}
