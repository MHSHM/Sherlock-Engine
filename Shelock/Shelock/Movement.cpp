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

	Transform* transform_component = owner->Get_Transform_component(); 

	int forward_state = glfwGetKey(owner->Get_Game()->Get_Window(), input_table[forward_key]);
	
	if (forward_state == GLFW_PRESS)
	{
		glm::vec3 current_pos = transform_component->Get_Position(); 
		current_pos += forward_speed * transform_component->Get_Forward() * delta_time; 
		transform_component->Set_Position(current_pos); 
	}

	int backward_state = glfwGetKey(owner->Get_Game()->Get_Window(), input_table[backward_key]);
	
	if (backward_state == GLFW_PRESS)
	{
		glm::vec3 current_pos = transform_component->Get_Position();
		current_pos += -1.0f * forward_speed * transform_component->Get_Forward() * delta_time;
		transform_component->Set_Position(current_pos);
	}

	// Yaw rotation
	int ccw_state = glfwGetKey(owner->Get_Game()->Get_Window(), input_table[ccw_rotation_key]); 
	Rotation current_ccw_rotation = transform_component->Get_Rotation();
	current_ccw_rotation.axis = transform_component->Get_Up(); 

	if (ccw_state == GLFW_PRESS) 
	{
		current_ccw_rotation.angle += angular_speed * delta_time;
		transform_component->Set_Rotation(current_ccw_rotation);
	}

	int cw_state = glfwGetKey(owner->Get_Game()->Get_Window(), input_table[cw_rotation_key]); 
	Rotation current_cw_rotation = transform_component->Get_Rotation();
	current_cw_rotation.axis = transform_component->Get_Up();

	if (cw_state == GLFW_PRESS) 
	{
		current_cw_rotation.angle += -1.0f * angular_speed * delta_time;
		transform_component->Set_Rotation(current_cw_rotation); 
	}
}
