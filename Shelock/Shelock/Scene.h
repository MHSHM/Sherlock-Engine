#pragma once

#include <vector>

class Scene
{
public:
	Scene(); 

	void Add_Scene_Node(class SceneNode* node); 
	void Remove_Scene_Node(class SceneNode* node); 

	std::vector<class SceneNode*>& Get_Scene_Nodes() { return scene_nodes;  }

	void Clear_Scene(); 

	~Scene();

private:

	std::vector<class SceneNode*> scene_nodes; 

};

