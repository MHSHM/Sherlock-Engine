#pragma once

#include "Mesh.h"
#include "Texture.h"

#include <vector>
#include <string>

class SkyBox
{
public:

	void Init(const std::vector<std::string>& faces_paths);

	VertexArrayObject vao;
	Texture cube_map; 
};

