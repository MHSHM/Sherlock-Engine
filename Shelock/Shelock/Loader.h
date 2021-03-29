#pragma once

#include "Scene.h"
#include "Mesh.h"

#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Loader
{
public:
	Loader() = default; 


	class SceneNode* Load(Scene& scene, const std::string& path); 

private:
	class SceneNode* Process_Node(const aiNode* node, Scene& scene);
	std::vector<Mesh> Process_Meshes(); 

	const aiScene* imported_scene; 
};

