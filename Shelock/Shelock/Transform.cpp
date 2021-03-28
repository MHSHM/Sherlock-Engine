
#include "Scene.h"



Transform::Transform(Actor* _owner):
	Component(_owner),
	position(glm::vec3(0.0f, 0.0f, 0.0f)), 
	scale(1.0f),
	rotation(),
	world_matrix(glm::mat4x4(1.0f)),
	recompute_world_matrix(true)
{
}

void Transform::Update(float delta_time)
{
	if (recompute_world_matrix) 
	{
		glm::mat4x4 translation_matrix = glm::translate(glm::mat4(), position); 
		glm::mat4x4 scale_matrix = glm::scale(glm::mat4(), glm::vec3(scale)); 
		glm::mat4x4 rotation_matrix = glm::rotate(glm::radians(rotation.angle), rotation.axis);
		world_matrix = translation_matrix * scale_matrix * rotation_matrix; 

		recompute_world_matrix = false; 
	}
}

void Transform::Set_Position(const glm::vec3& _position)
{
	recompute_world_matrix = true; 
	position = _position; 
}

void Transform::Set_Scale(const float& _scale)
{
	recompute_world_matrix = true; 
	scale = _scale; 
}

void Transform::Set_Rotation(const glm::vec3& _axis, const float& _angle)
{
	recompute_world_matrix = true; 
	rotation.axis = _axis; 
	rotation.angle = _angle; 
}

Transform::~Transform()
{

}
