#pragma once

#include "SceneNode.h"
#include "ComponentManager.h"

#include <vector>

#define MAX_SCENE_NODES 100

class Scene
{
public:
	Scene(class Game* _game);

	SceneNode* Add_Scene_Node(SceneNode node);
	void Remove_Scene_Node(SceneNode* node);

	ComponentManager<Transform> transform_manager;
	ComponentManager<Camera> camera_manager;
	ComponentManager<Movement> movement_manager;

	ComponentManager<Model> model_manager;
	ComponentManager<PointLight> point_light_manager;
	ComponentManager<SpotLight> spot_light_manager;

	std::vector<SceneNode> scene_nodes;
	std::vector<Actor> scene_actors;

	class Game* game;

	// Active scene camera
	class SceneNode* camera;

	~Scene();
};