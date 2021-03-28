#pragma once

#include "SceneNode.h"
#include "Actor.h"
#include "Transform.h"
#include "Model.h"


#include <vector>


#define MAX_SCENE_NODES 100

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

	class Game* Get_Game() { return game; }

	~Scene();

private:

	std::vector<SceneNode> scene_nodes; 
	std::vector<Actor> scene_actors; 
	std::vector<Transform> scene_nodes_transforms; 
	std::vector<Model> scene_nodes_models; 

	class Game* game; 

};

