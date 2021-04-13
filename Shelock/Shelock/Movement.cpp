#include "Movement.h"
#include "Game.h"

Movement::Movement(Actor* _owner):
	Component(_owner),
	forward_key('w'),
	backward_key('s'),
	ccw_rotation_key('a'),
	cw_rotation_key('d'),
	forward_speed(2.0f),
	angular_speed(2.0f)
{

	int key = 65; 
	for (char i = 'a'; i <= 'z'; ++i)
	{
		input_table[i] = key++; 
	}
}


void Movement::Update(float delta_time)
{
	Transform* transform_component = owner->Get_Component<Transform>(); 

	int forward_state = glfwGetKey(owner->game->window, input_table[forward_key]);
	
	if (forward_state == GLFW_PRESS)
	{
		glm::vec3 current_pos = transform_component->position; 
		current_pos += forward_speed * transform_component->forward * delta_time; 
		transform_component->Set_Position(current_pos); 
	}

	int backward_state = glfwGetKey(owner->game->window, input_table[backward_key]);
	
	if (backward_state == GLFW_PRESS)
	{
		glm::vec3 current_pos = transform_component->position;
		current_pos += -1.0f * forward_speed * transform_component->forward * delta_time;
		transform_component->Set_Position(current_pos);
	}

	// Yaw rotation
	int ccw_state = glfwGetKey(owner->game->window, input_table[ccw_rotation_key]); 

	if (ccw_state == GLFW_PRESS) 
	{
		glm::mat4 current_yaw_rotation = transform_component->yaw_rotation;
		glm::mat4 yaw = glm::rotate(angular_speed * delta_time, transform_component->up); 
		transform_component->Set_Rotation_Yaw(current_yaw_rotation * yaw);
	}

	int cw_state = glfwGetKey(owner->game->window, input_table[cw_rotation_key]);
	
	if (cw_state == GLFW_PRESS) 
	{
		glm::mat4 current_yaw_rotation = transform_component->yaw_rotation;
		glm::mat4 yaw = glm::rotate(-angular_speed * delta_time, transform_component->up);
		transform_component->Set_Rotation_Yaw(current_yaw_rotation * yaw);
	}
}
