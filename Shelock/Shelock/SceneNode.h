#pragma once

#include "Scene.h"

#include <vector>

class SceneNode
{
public:

	SceneNode(Scene& scene); 

	void Add_Child(SceneNode* child); 
	void Remove_Child(SceneNode* child);

	class Actor* Get_Actor() { return actor;  }
	std::vector<SceneNode*>& Get_Children() { return children;  }

	~SceneNode(); 

private:
	class Actor* actor; 
	SceneNode* parent; 
	std::vector<SceneNode*> children; 
};

