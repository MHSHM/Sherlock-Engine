#include "Scene.h"



Transform::Transform(Actor* _owner):
	Component(_owner),
	position(glm::vec3(0.0f, 0.0f, 0.0f)), 
	scale(1.0f),
	yaw_rotation(glm::mat4(1.0f)),
	pitch_rotation(glm::mat4(1.0f)),
	roll_rotation(glm::mat4(1.0f)),
	world_matrix(glm::mat4x4(1.0f)),
	recompute_world_matrix(true),
	forward(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f))
{
}

void Transform::Update(float delta_time)
{
	if (recompute_world_matrix)
	{
		glm::mat4x4 translation_matrix = glm::translate(glm::mat4(1.0f), position); 
		glm::mat4x4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale)); 
		glm::mat4x4 rotation_matrix = roll_rotation * pitch_rotation * yaw_rotation; 
		world_matrix = translation_matrix * scale_matrix * rotation_matrix; 

		recompute_world_matrix = false; 
	}

	forward = glm::vec3(world_matrix * glm::vec4(glm::vec3(0.0f, 0.0f, -1.0f), 0.0f));
	up = glm::vec3(world_matrix * glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	right = glm::vec3(world_matrix * glm::vec4(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));

	forward = glm::normalize(forward); 
	up = glm::normalize(up); 
	right = glm::normalize(right); 
}

void Transform::Set_Position(const glm::vec3 _position)
{
	recompute_world_matrix = true; 
	position = _position; 
}

void Transform::Set_Scale(const float _scale)
{
	recompute_world_matrix = true; 
	scale = _scale; 
}

void Transform::Set_Rotation_Yaw(const glm::mat4& _yaw)
{
	yaw_rotation = _yaw; 
	recompute_world_matrix = true; 
}

void Transform::Set_Rotation_pitch(const glm::mat4& _pitch)
{
	pitch_rotation = _pitch; 
	recompute_world_matrix = true; 
}

void Transform::Set_Rotation_roll(const glm::mat4& _roll)
{
	roll_rotation = _roll;
	recompute_world_matrix = true; 
}

