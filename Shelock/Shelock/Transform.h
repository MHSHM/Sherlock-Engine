#pragma once

#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"
#include "../Dependencies/GLM/mat4x4.hpp"
#include "../Dependencies/GLM/gtc/matrix_transform.hpp"
#include "../Dependencies/GLM/gtx/transform.hpp"

struct Rotation 
{
	Rotation() :
		axis(glm::vec3(0.0f, 1.0f, 0.0f)),
		angle(0.0f) 
	{
	
	}

	Rotation(const glm::vec3& _axis, const float& _angle) :
		axis(_axis),
		angle(_angle) 
	{
	
	}

	glm::vec3 axis; 
	
	float angle; 
};

class Transform : public Component
{
public:
	Transform(Actor* _owner); 

	void Update(float delta_time) override;

	void Set_Position(const glm::vec3 _position); 
	void Set_Scale(const float _scale); 
	void Set_Rotation_Yaw(const glm::mat4& _yaw); 
	void Set_Rotation_pitch(const glm::mat4& _pitch); 
	void Set_Rotation_roll(const glm::mat4& _roll); 
	
	glm::vec3 position; 
	float scale; 
	glm::mat4 yaw_rotation; 
	glm::mat4 pitch_rotation; 
	glm::mat4 roll_rotation; 

	glm::mat4x4 world_matrix; 
	bool recompute_world_matrix; 

	glm::vec3 forward; 
	glm::vec3 up;
	glm::vec3 right; 

};

