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


	void Load(Scene& scene, const std::string& path); 

private:
	void Process_Node(const aiNode* node, Scene& scene, class SceneNode* parent);
	std::vector<Mesh> Process_Meshes(const aiNode* node); 

	aiMesh** scene_meshes;
	aiMaterial** scene_materials;
	aiNode* scene_root; 
};

