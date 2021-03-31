#include "Renderer.h"
#include "Game.h"

#include <glew.h>
#include <glfw3.h>

Renderer::Renderer(Game* _game):
	game(_game)
{
}

void Renderer::Draw(Scene& scene, Framebuffer& render_target)
{
	render_target.Bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);





	render_target.Un_Bind(); 
}

void Renderer::Load_Shaders()
{
	//Shader shader;
	//shader.Create_Shader_Program("shader.vert", "shader.frag");
	//shaders.push_back(std::move(shader)); 
	//shaders_table["basic"] = &(shaders.back()); 
}
