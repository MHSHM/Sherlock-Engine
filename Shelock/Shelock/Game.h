#pragma once

#define GLEW_STATIC

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static float time_since_last_frame = 0.0f; 

#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "Scene.h"
#include "Loader.h"
#include "Renderer.h"

class Game 
{
public:
	
	Game(); 
	~Game(); 


	bool Initialize(); 
	void Run_Game(); 
	void Shutdown_Game(); 

	Scene& Get_Scene() { return scene;  }
	GLFWwindow* Get_Window() { return window; }


private:
	void Process_Input(); 
	void Update(); 
	void Generate_Output(); 
	bool Initialize_Framebuffers();

private:
	GLFWwindow* window;

	Scene scene; 
	Loader loader; 
	Renderer renderer;

	// Render targets
	Framebuffer default_render_target;

	bool game_running; 
};