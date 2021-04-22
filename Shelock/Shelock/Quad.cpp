#include "Quad.h"

#include <vector>

void Quad::Init()
{
	std::vector<Vertex> quad_vertices(4);

	quad_vertices[0].position = { 1.0f,  1.0f, 0.0f };
	quad_vertices[0].uv_coord = { 1.0f, 1.0f };

	quad_vertices[1].position = { 1.0f, -1.0f, 0.0f };
	quad_vertices[1].uv_coord = { 1.0f, 0.0f };

	quad_vertices[2].position = { -1.0f, -1.0f, 0.0f };
	quad_vertices[2].uv_coord = { 0.0f, 0.0f };

	quad_vertices[3].position = { -1.0f,  1.0f, 0.0f };
	quad_vertices[3].uv_coord = { 0.0f, 1.0f };

	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };

	vao.Init(quad_vertices, indices, VertexLayout::PositionUv);
}
