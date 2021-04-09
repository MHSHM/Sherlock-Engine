#include "Game.h"

Game::Game() :
	game_running(true),
	window(nullptr),
	scene(this),
	renderer(this)
{
	
}

bool Game::Initialize()
{
	if (!glfwInit())
	{
		std::cerr << "failed to Initialize GLFW!\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sherlock", NULL, NULL);
	if (!window)
	{
		std::cerr << "failed to create window!\n"; 
		return false; 
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false; 
	}

	bool check = Initialize_Framebuffers(); 
	if (!check) 
	{
		std::cerr << "Failed to initialize framebuffers\n";
		return false; 
	}

	renderer.Load_Shaders(); 

	Load_Scene_Data(); 

	return true;
}

void Game::Run_Game()
{
	while (game_running) 
	{
		Process_Input(); 
		Update(); 
		Generate_Output(); 
	}
}

void Game::Process_Input()
{
	game_running = !glfwWindowShouldClose(window); 

	glfwPollEvents();
}

void Game::Update()
{

	float delta_time = glfwGetTime() - time_since_last_frame;
	time_since_last_frame = glfwGetTime();

	/*
	for (int i = 0; i < scene.scene_actors.size(); ++i) 
	{
		for (int j = 0; j < scene.scene_actors[i].components.size(); ++j) 
		{
			scene.scene_actors[i].components[j]->Update(delta_time); 
		}
	}
	*/

	
	for (int i = 0; i < scene.movement_manager.components.size(); ++i) 
	{
		scene.movement_manager.components[i].Update(delta_time);
	}

	for (int i = 0; i < scene.transform_manager.components.size(); ++i) 
	{
		scene.transform_manager.components[i].Update(delta_time); 
	}

	for (int i = 0; i < scene.camera_manager.components.size(); ++i) 
	{
		scene.camera_manager.components[i].Update(delta_time);
	}

	for (int i = 0; i < scene.point_light_manager.components.size(); i++) 
	{
		scene.point_light_manager.components[i].Update(delta_time); 
	}

	for (int i = 0; i < scene.spot_light_manager.components.size(); ++i) 
	{
		scene.spot_light_manager.components[i].Update(delta_time); 
	}
	
}

void Game::Generate_Output()
{
	renderer.Draw(scene, default_render_target); 


 	glfwSwapBuffers(window); 
}

bool Game::Initialize_Framebuffers()
{

	return true; 
}

void Game::Load_Scene_Data()
{
	SceneNode* helmet = loader.Load(scene, "Models/HelmetPresentationLightMap.fbx");
	helmet->actor->Get_Component<Transform>()->Set_Position(glm::vec3(1.0f, 1.0f, -3.0f)); 
	helmet->actor->Get_Component<Transform>()->Set_Scale(0.3f);

	SceneNode* backpack = loader.Load(scene, "Models/backpack.obj");
	backpack->actor->Get_Component<Transform>()->Set_Position(glm::vec3(-1.0f, 0.0f, -3.0f));
	backpack->actor->Get_Component<Transform>()->Set_Scale(0.3f);

	SceneNode* camera = scene.Add_Scene_Node(SceneNode(&scene));
	scene.transform_manager.Add_Component(camera->actor); 
	camera->actor->Get_Component<Transform>()->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f)); 
	scene.camera_manager.Add_Component(camera->actor);
	scene.point_light_manager.Add_Component(camera->actor); 
	scene.movement_manager.Add_Component(camera->actor);
	//scene.spot_light_manager.Add_Component(camera->actor); 
	scene.camera = camera;
}


void Game::Shutdown_Game()
{
	glfwTerminate();
}

Game::~Game() 
{
}