#include "Game.h"

Game::Game() :
	game_running(true)
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
}

void Game::Generate_Output()
{

}

void Game::Shutdown_Game()
{
	glfwTerminate();
}

Game::~Game() 
{
}