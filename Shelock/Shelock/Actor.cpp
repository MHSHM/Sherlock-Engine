#include "Scene.h"
#include "Game.h"

Actor::Actor(Game* _game):
	game(_game)
{
}

void Actor::Clear() 
{
	game->scene.transform_manager.Remove_Component(this, Get_Component<Transform>());
	game->scene.model_manager.Remove_Component(this, Get_Component<Model>()); 
	game->scene.FBSCamera_manager.Remove_Component(this, Get_Component<FPSCamera>());
	game->scene.movement_manager.Remove_Component(this, Get_Component<Movement>()); 
	game->scene.point_light_manager.Remove_Component(this, Get_Component<PointLight>()); 
	game->scene.spot_light_manager.Remove_Component(this, Get_Component<SpotLight>());
}