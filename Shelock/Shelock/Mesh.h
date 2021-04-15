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
	glm::vec3 tangent; 
};

struct Material 
{
	class Texture* albedo_map; 
	class Texture* normal_map; 
	class Texture* metalic_map; 
	class Texture* roughness_map; 
	class Texture* AO_map; 
};

class Mesh
{
public:

	Mesh() = default;

	Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
		std::vector<glm::vec2> uv_coords, std::vector<glm::vec3> tangents, std::vector<unsigned int> _indices);
	
	std::vector<Vertex> vertices; 
	std::vector<unsigned int> indices;
	VertexArrayObject VAO;
	Material material;
};

