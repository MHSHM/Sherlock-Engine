#include "Actor.h"
#include "Camera.h"
#include "Transform.h"

Camera::Camera(Actor* _owner):
	Component(_owner),
	near_plane(0.3f),
	far_plane(1000.0f),
	field_of_view(90.0f),
	camera_forward(glm::vec3(0.0f, 0.0f, -1.0f)),
	camera_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	camera_right(glm::vec3(1.0f, 0.0f, 0.0f))
{
}

void Camera::Update(float delta_time)
{
	Transform* transform = owner->Get_Transform_component();

	view = glm::lookAt(transform->Get_Position(), camera_forward * far_plane, glm::vec3(0.0f, 1.0f, 0.0f)); 

	float aspect_ratio = 1280.0f / 720.0f; 
	projection = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_plane, far_plane); 
}