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

	std::vector<Movement>& movements = scene.Get_Movements(); 

	for (int i = 0; i < movements.size(); ++i) 
	{
		movements[i].Update(delta_time); 
	}

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

	std::vector<PointLight>& point_lights = scene.Get_Point_Lights();

	for (int i = 0; i < point_lights.size(); ++i)
	{
		point_lights[i].Update(delta_time);
	}

	std::vector<SpotLight>& spot_lights = scene.Get_Spot_Lights(); 

	for (int i = 0; i < spot_lights.size(); ++i) 
	{
		spot_lights[i].Update(delta_time); 
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
	helmet->Get_Actor()->Get_Transform_component()->Set_Position(glm::vec3(0.0f, 1.0f, -3.0f));
	helmet->Get_Actor()->Get_Transform_component()->Set_Scale(0.3f);
	//scene_node->Get_Actor()->Add_Component(ComponentType::MovementComp); 

	SceneNode* backback = loader.Load(scene, "Models/backpack.obj"); 
	backback->Get_Actor()->Get_Transform_component()->Set_Position(glm::vec3(3.0f, 0.0f, -3.0f));
	backback->Get_Actor()->Get_Transform_component()->Set_Scale(0.3f);
	//backback->Get_Actor()->Add_Component(ComponentType::MovementComp); 
	//backback->Get_Actor()->Add_Component(ComponentType::PointLightComp); 

	SceneNode* camera = scene.Add_Scene_Node(SceneNode(&scene));
	camera->Get_Actor()->Add_Component(ComponentType::TransformComp);
	camera->Get_Actor()->Get_Transform_component()->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
	camera->Get_Actor()->Add_Component(ComponentType::CameraComp);
	//camera->Get_Actor()->Add_Component(ComponentType::SpotLightComp);
	//camera->Get_Actor()->Add_Component(ComponentType::PointLightComp); 
	camera->Get_Actor()->Add_Component(ComponentType::MovementComp); 
	scene.Set_Active_Camera(camera);
}


void Game::Shutdown_Game()
{
	glfwTerminate();
}

Game::~Game() 
{
}