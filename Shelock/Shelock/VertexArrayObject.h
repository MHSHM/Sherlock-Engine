#pragma once

#include <vector>

class VertexArrayObject
{
public:
	
	VertexArrayObject() = default; 

	void Init(std::vector<struct Vertex>& vertices, std::vector<unsigned int>& indices);

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

