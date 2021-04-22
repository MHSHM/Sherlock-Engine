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
#include "Quad.h"

class Game 
{
public:
	
	Game(); 
	~Game(); 


	bool Initialize(); 
	void Run_Game(); 
	void Shutdown_Game(); 

	void Process_Input(); 
	void Update(); 
	void Generate_Output(); 
	bool Initialize_Framebuffers();
	void Load_Scene_Data();

	GLFWwindow* window;

	Scene scene; 
	Loader loader; 
	Renderer renderer;

	// Render targets
	Framebuffer default_render_target;
	Framebuffer hdr_render_target; 
	Quad quad; 

	bool game_running; 
	bool lock_cursor; 
};