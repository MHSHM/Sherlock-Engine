#pragma once

#include <vector>

#define MAX_CHILDREN 10

class SceneNode
{
public:

	SceneNode(class Scene* _scene); 

	void Add_Child(SceneNode* child); 
	void Remove_Child(SceneNode* child);

	class Actor* Get_Actor() { return actor;  }
	class Scene* Get_Scene() { return scene;  }
	SceneNode* Get_Parent() { return parent;  }
	std::vector<SceneNode*>& Get_Children() { return children;  }



	void Set_Actor(class Actor* _actor) { actor = _actor;  }

	inline bool operator==(const SceneNode& other) 
	{
		return (this == &other); 
	}

	~SceneNode();

private:
	class Actor* actor;
	class Scene* scene; 
	SceneNode* parent; 
	std::vector<SceneNode*> children; 
};

