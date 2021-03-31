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

	std::vector<Transform>& transforms = scene.Get_Transforms(); 

	for (int i = 0; i < transforms.size(); ++i) 
	{
		transforms[i].Update(delta_time); 
	}

	std::vector<Camera>& cameras = scene.Get_Cameras(); 

	for (int i = 0; i < cameras.size(); ++i) 
	{
		cameras[i].Update(delta_time); 
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
	SceneNode* scene_node = loader.Load(scene, "Models/backpack.obj");
	scene_node->Get_Actor()->Get_Transform_component()->Set_Position(glm::vec3(0.0f, 0.0f, -1.0f));
	scene_node->Get_Actor()->Get_Transform_component()->Set_Scale(0.3f);

	SceneNode* camera = scene.Add_Scene_Node(SceneNode(&scene));
	camera->Get_Actor()->Add_Component(ComponentType::TransformComp);
	camera->Get_Actor()->Get_Transform_component()->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
	camera->Get_Actor()->Add_Component(ComponentType::CameraComp);
	scene.Set_Active_Camera(camera);
}


void Game::Shutdown_Game()
{
	glfwTerminate();
}

Game::~Game() 
{
}