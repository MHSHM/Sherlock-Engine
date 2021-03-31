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


	std::vector<Model>& model_comps = scene.Get_Models(); 
	
	for (auto& model_comp : model_comps) 
	{
		std::vector<Mesh>& meshses = model_comp.Get_Meshes(); 
		
		shaders_table["basic"]->Bind(); 
		
		shaders_table["basic"]->Set_Matrix4_Uniform("u_world_matrix", model_comp.Get_Owner()->Get_Transform_component()->Get_World_Matrix());
		shaders_table["basic"]->Set_Matrix4_Uniform("u_view_matrix", scene.Get_Active_Camera()->Get_Actor()->Get_Camera_Component()->Get_View()); 
		shaders_table["basic"]->Set_Matrix4_Uniform("u_projection_matrix", scene.Get_Active_Camera()->Get_Actor()->Get_Camera_Component()->Get_Projection()); 

		for (auto& mesh : meshses) 
		{
			mesh.Get_VAO().Bind(); 
			glDrawElements(GL_TRIANGLES, mesh.Get_VAO().Get_Element_Buffer_Size(), GL_UNSIGNED_INT, nullptr); 
		}
	}

	render_target.Un_Bind(); 
}

void Renderer::Load_Shaders()
{
	Shader shader;
	shader.Create_Shader_Program("Shaders/shader.vert", "Shaders/shader.frag");
	shaders.push_back(std::move(shader)); 
	shaders_table["basic"] = &(shaders.back()); 
}
