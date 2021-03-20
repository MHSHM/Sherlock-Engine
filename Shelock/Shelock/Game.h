#pragma once

#define GLEW_STATIC

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <glew.h>
#include <glfw3.h>
#include <iostream>

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
	void Update_Game(); 
	void Generate_Output(); 


private:
	bool game_running; 

	GLFWwindow* window; 
};