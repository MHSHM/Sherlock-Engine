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
	SceneNode* Get_Parent() { return parent;  }
	std::vector<SceneNode*>& Get_Children() { return children;  }

	void Set_Actor(class Actor* _actor) { actor = _actor;  }

	~SceneNode(); 

private:
	class Actor* actor; 
	SceneNode* parent; 
	std::vector<SceneNode*> children; 
};

