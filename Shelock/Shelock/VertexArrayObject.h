#pragma once

#include <vector>

enum class VertexLayout
{
	Position = 0, 
	PositionUv = 1,
	PositionUvNormal = 2, 
	PositionUvNormalTangent = 3
};

class VertexArrayObject
{
public:
	
	VertexArrayObject() = default; 

	void Init(std::vector<struct Vertex>& vertices, std::vector<unsigned int>& indices, const VertexLayout& layout);

	void Bind(); 
	void Un_Bind(); 

	unsigned int Get_VAO() { return vertex_array_obj_id;  }
	unsigned int Get_Element_Buffer_Size() { return element_buffer_size; }

	void Clear(); 

private:
	unsigned int vertex_array_obj_id; 
	unsigned int array_buffer_id; 
	unsigned int element_buffer_id; 
	unsigned int element_buffer_size; 
};

