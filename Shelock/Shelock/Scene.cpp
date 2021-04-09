#include "Scene.h"
#include "Game.h"
#include "Camera.h"


Scene::Scene(Game* _game):
	game(_game)
{
	scene_nodes.reserve(MAX_SCENE_NODES); 
	scene_actors.reserve(MAX_SCENE_NODES);
	transform_manager.Init(); 
	camera_manager.Init(); 
	movement_manager.Init(); 
	model_manager.Init(); 
	point_light_manager.Init(); 
	spot_light_manager.Init(); 
}

SceneNode* Scene::Add_Scene_Node(SceneNode node)
{
	scene_nodes.push_back(node); 
	return &scene_nodes.back();
}

void Scene::Remove_Scene_Node(SceneNode* node)
{
	
	if (node->parent) 
	{
		node->parent->Remove_Child(node); 
	}

	for (auto child : node->children) 
	{
		Remove_Scene_Node(child); 
	}

	// Here to delete a scene node we swap the node with the back of the vector
	// to avoid shifting when using erase
	// we still need to fix the children of the back as they will be pointing 
	// to different parent after swapping
	auto iter1 = std::find(scene_nodes.begin(), scene_nodes.end(), *node);
	
	for (auto& child : scene_nodes.back().children) 
	{
		child->parent = (&(*iter1)); 
	}

	// Same when removing an actor we need to fix the owner of the components of the 
	// scene_actors.back() because they will have a false parent after swapping
	auto iter2 = std::find(scene_actors.begin(), scene_actors.end(), *(node->actor));
	
	for (auto& component : scene_actors.back().components) 
	{
		component->owner = (&(*iter2)); 
	}

	std::iter_swap(iter1, scene_nodes.end() - 1);
	std::iter_swap(iter2, scene_actors.end() - 1);

	scene_nodes.pop_back();

	scene_actors.back().Clear(); 
	scene_actors.pop_back(); 
}

Scene::~Scene()
{
}
