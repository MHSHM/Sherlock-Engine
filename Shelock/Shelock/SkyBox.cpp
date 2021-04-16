
#include "SkyBox.h"

#include "../Dependencies/stb_image/stb_image.h"

#include <glew.h>

void SkyBox::Init(const std::vector<std::string>& faces_paths)
{
	std::vector<Vertex> cube_vertices(8); 

	cube_vertices[0].position = { -1.0f, -1.0f,  1.0f };
	cube_vertices[1].position = {  1.0f, -1.0f,  1.0f };
	cube_vertices[2].position = {  1.0f,  1.0f,  1.0f };
	cube_vertices[3].position = { -1.0f,  1.0f,  1.0f };
	cube_vertices[4].position = { -1.0f, -1.0f,  -1.0f };
	cube_vertices[5].position = {  1.0f, -1.0f,  -1.0f };
	cube_vertices[6].position = {  1.0f,  1.0f,  -1.0f };
	cube_vertices[7].position = { -1.0f,  1.0f,  -1.0f };

	std::vector<unsigned int> cube_elements = {
		0, 1, 2, 2, 3, 0, 1, 5, 6,
		6, 2, 1, 7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4, 4, 5, 1,
		1, 0, 4, 3, 2, 6, 6, 7, 3
	};

	vao.Init(cube_vertices, cube_elements, VertexLayout::Position);

	cube_map.Create_Cube_Map(faces_paths);
}
