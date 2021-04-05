
#include "Scene.h"



Transform::Transform(Actor* _owner):
	Component(_owner),
	position(glm::vec3(0.0f, 0.0f, 0.0f)), 
	scale(1.0f),
	rotation(),
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
		glm::mat4x4 rotation_matrix = glm::rotate(rotation.angle, rotation.axis);
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

void Transform::Set_Rotation(const Rotation _rotation)
{
	recompute_world_matrix = true; 
	rotation = _rotation;
}

Transform::~Transform()
{

}
