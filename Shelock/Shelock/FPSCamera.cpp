#include "Game.h"
#include "Actor.h"
#include "FPSCamera.h"
#include "Transform.h"

#include "../Dependencies/GLM/gtx/rotate_vector.hpp"

#include <glfw3.h>
#include <iostream>

#define EPSILON 0.1f

FPSCamera::FPSCamera(Actor* _owner):
	Component(_owner),
	near_plane(0.1f),
	far_plane(1000.0f),
	field_of_view(90.0f),
	sensitivity(10.0f),
	forward_speed(2.0f),
	forward(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f))
{
}

void FPSCamera::Update(float delta_time)
{	

	Transform* transform = owner->Get_Component<Transform>();

	if (owner->game->lock_cursor)
	{

		static double mouse_x = 0.0, mouse_y = 0.0;

		double last_x = mouse_x;
		double last_y = mouse_y; 

		glfwGetCursorPos(owner->game->window, &mouse_x, &mouse_y);

		double current_x = ((mouse_x - last_x) / 10.0) * delta_time;
		double current_y = ((mouse_y - last_y) / 10.0) * delta_time; 

		// cos angle between camera forward and world up
		float cos_a = glm::dot(forward, glm::vec3(0.0f, 1.0f, 0.0f)); 

		// cos angle between camera forward and world down
		float cos_b = glm::dot(forward, glm::vec3(0.0f, -1.0f, 0.0f));

		// cos min angle between cam forward and world up, down
		// cos(20)
		float cos_c = 0.8660f;

		if (fabs(cos_a - cos_c) < EPSILON)
		{
			if (current_y < 0.0) current_y = 0.0;
		}

		if (fabs(cos_b - cos_c) < EPSILON) 
		{
			if (current_y > 0.0) current_y = 0.0; 
		}
		
		forward = glm::normalize(glm::rotate(forward, float(-current_x), up));
		right = glm::normalize(glm::cross(forward, up));
		forward = glm::normalize(glm::rotate(forward, float(-current_y), right));


		int forward_state = glfwGetKey(owner->game->window, GLFW_KEY_W);
		if (forward_state == GLFW_PRESS) transform->Set_Position(transform->position + (forward_speed * forward * delta_time));

		int backward_state = glfwGetKey(owner->game->window, GLFW_KEY_S);
		if (backward_state == GLFW_PRESS) transform->Set_Position(transform->position + (-forward_speed * forward * delta_time));

		int left_state = glfwGetKey(owner->game->window, GLFW_KEY_A);
		if (left_state == GLFW_PRESS) transform->Set_Position(transform->position + (-forward_speed * right * delta_time));

		int right_state = glfwGetKey(owner->game->window, GLFW_KEY_D);
		if (right_state == GLFW_PRESS) transform->Set_Position(transform->position + (forward_speed * right * delta_time));
	}

	view = glm::lookAt(transform->position, forward * 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	float aspect_ratio = 1280.0f / 720.0f; 
	projection = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_plane, far_plane); 
	
}
