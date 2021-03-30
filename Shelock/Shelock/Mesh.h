#pragma once

#include <vector>

#include "../Dependencies/GLM/vec3.hpp"
#include "../Dependencies/GLM/vec2.hpp"

#include "VertexArrayObject.h"
#include "Shader.h"

struct Vertex
{
	Vertex() :
		position(glm::vec3(0.0f, 0.0f, 0.0f)),
		normal(glm::vec3(0.0f, 0.0f, 0.0f)),
		uv_coord(glm::vec2(0.0f, 0.0f)) 
	{
		
	}

	glm::vec3 position; 
	glm::vec3 normal; 
	glm::vec2 uv_coord; 
};

class Mesh
{
public:

	Mesh() = default;

	Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
		std::vector<glm::vec2> uv_coords, std::vector<unsigned int> _indices);

	VertexArrayObject& Get_VAO() { return VAO; }
	Shader& Get_Sahder() { return shader; }

private:
	
	std::vector<Vertex> vertices; 
	std::vector<unsigned int> indices;
	VertexArrayObject VAO; 
	Shader shader; 
};

