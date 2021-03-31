#pragma once

#include "Scene.h"
#include "Framebuffer.h"
#include "Shader.h"

#include <vector>
#include <unordered_map>

class Renderer
{
public:
	Renderer(class Game* _game);



	void Draw(Scene& scene, Framebuffer& render_target); 
	
	void Load_Shaders(); 

private:
	class Game* game;

	std::vector<Shader> shaders; 
	std::unordered_map<std::string, Shader*> shaders_table;
};

