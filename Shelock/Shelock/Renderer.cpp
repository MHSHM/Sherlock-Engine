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
	glDisable(GL_DEPTH_TEST);

	// Draw Skybox
	shaders_table["skybox"]->Bind(); 
	
	glm::mat4 world = glm::mat4(1.0f); 
	glm::mat4 view  = scene.camera->actor->Get_Component<FPSCamera>()->view;
	glm::mat4 projection = scene.camera->actor->Get_Component<FPSCamera>()->projection; 

	shaders_table["skybox"]->Set_Matrix4_Uniform("u_world", world);
	shaders_table["skybox"]->Set_Matrix4_Uniform("u_view", view);
	shaders_table["skybox"]->Set_Matrix4_Uniform("u_projection", projection);

	scene.sky_box.cube_map.Bind(0); 
	scene.sky_box.vao.Bind(); 

	glDrawElements(GL_TRIANGLES, scene.sky_box.vao.Get_Element_Buffer_Size(), GL_UNSIGNED_INT, nullptr);

	scene.sky_box.cube_map.Un_Bind(); 
	scene.sky_box.vao.Un_Bind();

	// Draw Scene
	glEnable(GL_DEPTH_TEST);
	shaders_table["basic"]->Bind();

	shaders_table["basic"]->Set_Int_Uniform("scene_point_lights", scene.point_light_manager.components.size()); 
	shaders_table["basic"]->Set_Int_Uniform("scene_spot_light", scene.spot_light_manager.components.size()); 
	
	shaders_table["basic"]->Set_Matrix4_Uniform("u_view_matrix", view);
	shaders_table["basic"]->Set_Matrix4_Uniform("u_projection_matrix", projection);
	
	shaders_table["basic"]->Set_Vec3_Uniform("dir_light.direction", scene.dir_light->actor->Get_Component<DirectionalLight>()->direction);
	shaders_table["basic"]->Set_Vec3_Uniform("dir_light.color", scene.dir_light->actor->Get_Component<DirectionalLight>()->color);

	for (int i = 0; i < scene.point_light_manager.components.size(); ++i)
	{
		std::string index = std::to_string(i); 
		PointLight current_pointlight = scene.point_light_manager.components[i];

		shaders_table["basic"]->Set_Vec3_Uniform("point_lights[" + index + "].position", current_pointlight.position);
		shaders_table["basic"]->Set_Vec3_Uniform("point_lights[" + index + "].color", current_pointlight.color);
		shaders_table["basic"]->Set_Float_Uniform("point_lights[" + index + "].radius", current_pointlight.radius);
		shaders_table["basic"]->Set_Float_Uniform("point_lights[" + index + "].linear", current_pointlight.linear);
		shaders_table["basic"]->Set_Float_Uniform("point_lights[" + index + "].quadratic", current_pointlight.quadratic);
		shaders_table["basic"]->Set_Float_Uniform("point_lights[" + index + "].falloff_distance", current_pointlight.falloff_distance);
	}
	
	for (int i = 0; i < scene.spot_light_manager.components.size(); ++i)
	{
		std::string index = std::to_string(i); 
		SpotLight current_spotlight = scene.spot_light_manager.components[i];

		shaders_table["basic"]->Set_Float_Uniform("spot_lights[" + index + "].u", current_spotlight.u);
		shaders_table["basic"]->Set_Float_Uniform("spot_lights[" + index + "].p", current_spotlight.p);
		shaders_table["basic"]->Set_Vec3_Uniform("spot_lights[" + index + "].position", current_spotlight.position);
		shaders_table["basic"]->Set_Vec3_Uniform("spot_lights[" + index + "].forward", current_spotlight.forward);
		shaders_table["basic"]->Set_Vec3_Uniform("spot_lights[" + index + "].color", current_spotlight.color);
	}
	

	for (auto& model_comp : scene.model_manager.components)
	{
		std::vector<Mesh>& meshses = model_comp.meshes; 
		
		Transform* transform = model_comp.owner->Get_Component<Transform>();

		shaders_table["basic"]->Set_Matrix4_Uniform("u_world_matrix", transform->world_matrix);

		for (auto& mesh : meshses) 
		{
			mesh.material.albedo_map->Bind(0); 
			shaders_table["basic"]->Set_Int_Uniform("surface_material.albedo", 0);
			
			mesh.material.normal_map->Bind(1); 
			shaders_table["basic"]->Set_Int_Uniform("surface_material.normals", 1);

			mesh.VAO.Bind(); 
			glDrawElements(GL_TRIANGLES, mesh.VAO.Get_Element_Buffer_Size(), GL_UNSIGNED_INT, nullptr);

			mesh.VAO.Un_Bind();
		}
	}

	render_target.Un_Bind(); 
}

void Renderer::Load_Shaders()
{

	shaders.reserve(10); 

	Shader shader;
	shader.Create_Shader_Program("Shaders/shader.vert", "Shaders/shader.frag");
	shaders.push_back(std::move(shader)); 
	shaders_table["basic"] = &(shaders.back());

	Shader skybox; 
	skybox.Create_Shader_Program("Shaders/Skybox.vert", "Shaders/Skybox.frag");
	shaders.push_back(std::move(skybox)); 
	shaders_table["skybox"] = &(shaders.back());
}
