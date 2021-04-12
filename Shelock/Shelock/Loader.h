#pragma once

#include "Scene.h"
#include "Mesh.h"
#include "Texture.h"

#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define MAX_TEXTURES 100

class Loader
{
public:
	Loader(); 
	~Loader();

	class SceneNode* Load(Scene& scene, const std::string& path); 
	Texture* Load_Texture(const std::string& path);

	std::vector< std::pair<std::string, Texture> > textures; 
	const aiScene* imported_scene;

private:
	class SceneNode* Process_Node(const aiNode* node, Scene& scene);
	std::vector<Mesh> Process_Meshes(); 
};

