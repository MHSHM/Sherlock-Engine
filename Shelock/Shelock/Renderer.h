#pragma once

#include "Scene.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Quad.h"

#include <vector>
#include <unordered_map>

class Renderer
{
public:
	Renderer(class Game* _game);



	void Draw(Scene& scene, Framebuffer& render_target); 
	void Draw_To_Quad(Texture& texture_to_draw, Quad quad, Framebuffer& render_target);

	void Load_Shaders(); 

	void Clear(); 

	class Game* game;

	std::vector<Shader> shaders; 
	std::unordered_map<std::string, Shader*> shaders_table;
};

