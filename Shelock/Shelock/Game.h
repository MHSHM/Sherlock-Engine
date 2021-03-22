#pragma once

#define GLEW_STATIC

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static float time_since_last_frame = 0.0f; 

#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "Scene.h"
#include "SceneNode.h"
#include "Actor.h"

class Game 
{
public:
	
	Game(); 
	~Game(); 


	bool Initialize(); 
	void Run_Game(); 
	void Shutdown_Game(); 


private:
	void Process_Input(); 
	void Update(); 
	void Generate_Output(); 


private:
	GLFWwindow* window;

	Scene scene; 
	

	bool game_running; 
};