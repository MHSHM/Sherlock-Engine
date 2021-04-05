#pragma once

#include "SceneNode.h"
#include "Actor.h"
#include "Transform.h"
#include "Model.h"
#include "Camera.h"
#include "Movement.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <vector>


#define MAX_SCENE_NODES 100
#define MAX_SCENE_POINT_LIGHTS 10
#define MAX_SCENE_SPOT_LIGHTS 10

class Scene
{
public:
	Scene(class Game* _game);

	SceneNode* Add_Scene_Node(SceneNode node);
	void Remove_Scene_Node(SceneNode* node);

	std::vector<SceneNode>& Get_Scene_Nodes() { return scene_nodes;  }
	std::vector<Actor>& Get_Scene_Actors() { return scene_actors;  }
	std::vector<Transform>& Get_Transforms() { return scene_nodes_transforms;  }
	std::vector<Model>& Get_Models() { return scene_nodes_models;  }
	std::vector<Camera>& Get_Cameras() { return scene_cameras; }
	std::vector<Movement>& Get_Movements() { return scene_nodes_movements; }
	class Game* Get_Game() { return game; }
	class SceneNode* Get_Active_Camera() { return camera; }

	std::vector<PointLight>& Get_Point_Lights() { return scene_point_lights; }
	std::vector<SpotLight>& Get_Spot_Lights() { return scene_spot_lights; }

	void Set_Active_Camera(class SceneNode* _camera) { camera = _camera; }

	~Scene();

private:

	std::vector<SceneNode> scene_nodes; 
	std::vector<Actor> scene_actors; 
	
	// Components
	std::vector<Transform> scene_nodes_transforms; 
	std::vector<Model> scene_nodes_models; 
	std::vector<Camera> scene_cameras; 
	std::vector<Movement> scene_nodes_movements; 

	// Lighting
	std::vector<PointLight> scene_point_lights; 
	std::vector<SpotLight> scene_spot_lights; 


	class Game* game; 

	// Active scene camera
	class SceneNode* camera; 
};

