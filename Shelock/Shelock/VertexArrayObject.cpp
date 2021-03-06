
#include "VertexArrayObject.h"
#include "Mesh.h"


#include <glew.h>

void VertexArrayObject::Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const VertexLayout& layout)
{
	element_buffer_size = indices.size(); 

	switch (layout)
	{

		case VertexLayout::Position: 
		{
			glGenVertexArrays(1, &vertex_array_obj_id);
			glBindVertexArray(vertex_array_obj_id);

			glGenBuffers(1, &array_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &element_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}
		break;

		case VertexLayout::PositionUv: 
		{
			glGenVertexArrays(1, &vertex_array_obj_id);
			glBindVertexArray(vertex_array_obj_id);

			glGenBuffers(1, &array_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &element_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv_coord));
		}	
		break; 


		case VertexLayout::PositionUvNormal: 
		{
			glGenVertexArrays(1, &vertex_array_obj_id);
			glBindVertexArray(vertex_array_obj_id);

			glGenBuffers(1, &array_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &element_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv_coord));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		}
		break; 

		case VertexLayout::PositionUvNormalTangent: 
		{
			glGenVertexArrays(1, &vertex_array_obj_id);
			glBindVertexArray(vertex_array_obj_id);

			glGenBuffers(1, &array_buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &element_buffer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv_coord));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		}
		break;
	}
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(vertex_array_obj_id);
}

void VertexArrayObject::Un_Bind()
{
	glBindVertexArray(0); 
}

void VertexArrayObject::Clear()
{
	glDeleteVertexArrays(1, &vertex_array_obj_id);
	glDeleteBuffers(1, &array_buffer_id);
	glDeleteBuffers(1, &element_buffer_id);
}
