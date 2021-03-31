#include "Scene.h"
#include "Game.h"

Actor::Actor(Game* _game):
	transform_component(nullptr),
	model_Component(nullptr),
	camera_component(nullptr),
	game(_game)
{
}

void Actor::Add_Component(const ComponentType& type)
{
	std::vector<Transform>& transforms = game->Get_Scene().Get_Transforms();
	std::vector<Model>& models = game->Get_Scene().Get_Models();
	std::vector<Camera>& cameras = game->Get_Scene().Get_Cameras(); 

	if (type == ComponentType::TransformComp) 
	{
		transforms.push_back(Transform(this));
		transform_component = &(transforms.back());
	}
	else if (type == ComponentType::ModelComp) 
	{
		models.push_back(Model(this)); 
		model_Component = &(models.back()); 
	}
	else if (type == ComponentType::CameraComp) 
	{
		cameras.push_back(Camera(this)); 
		camera_component = &(cameras.back());
	}
}

void Actor::Remove_Component(const ComponentType& type)
{
	std::vector<Transform>& transforms = game->Get_Scene().Get_Transforms(); 
	std::vector<Model>& models = game->Get_Scene().Get_Models(); 
	std::vector<Camera>& cameras = game->Get_Scene().Get_Cameras(); 

	if (type == ComponentType::TransformComp) 
	{
		auto iter = std::find(transforms.begin(), transforms.end(), *transform_component); 
		if (iter != transforms.end())
		{
			transforms.erase(iter); 
			transform_component = nullptr; 
		}
	}
	else if (type == ComponentType::ModelComp) 
	{
		auto iter = std::find(models.begin(), models.end(), *model_Component);
		if (iter != models.end())
		{
			models.erase(iter);
			model_Component = nullptr; 
		}
	}
	else if (type == ComponentType::CameraComp) 
	{
		auto iter = std::find(cameras.begin(), cameras.end(), *camera_component); 
		if (iter != cameras.end()) 
		{
			cameras.erase(iter); 
			camera_component = nullptr; 
		}
	}
}

Actor::~Actor()
{
	transform_component = nullptr; 
	model_Component = nullptr; 
}

