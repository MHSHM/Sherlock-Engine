#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
	std::vector<glm::vec2> uv_coords, std::vector<glm::vec3> tangents, std::vector<unsigned int> _indices) :
	indices(_indices)
{
	uint32_t num_vertices = positions.size();
	vertices.resize(num_vertices); 

	int layout = 0; 

	bool has_normals = (normals.size() > 0); 
	bool has_uvs = (uv_coords.size() > 0); 
	bool has_tangents = (tangents.size() > 0); 

	layout = has_normals + has_uvs + has_tangents;

	for (int i = 0; i < num_vertices; ++i) 
	{
		Vertex vertex;

		vertex.position = positions[i]; 

		if (has_normals) 
		{
			vertex.normal = normals[i]; 
		}

		if (has_uvs) 
		{
			vertex.uv_coord = uv_coords[i]; 
		}
		
		if (has_tangents) 
		{
			vertex.tangent = tangents[i]; 
		}
		
		vertices[i] = std::move(vertex);
	}

	VAO.Init(vertices, indices, static_cast<VertexLayout>(layout));
}