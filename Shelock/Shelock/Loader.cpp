#include "Loader.h"
#include "Scene.h"


Loader::Loader()
{
	textures.reserve(MAX_TEXTURES);
}

Loader::~Loader()
{
	for (auto& p : textures) 
	{
		p.second.Clear(); 
	}
}

SceneNode* Loader::Load(Scene& scene, const std::string& path)
{
	Assimp::Importer importer;

	 imported_scene = importer.ReadFile(path,
		aiProcess_Triangulate |
		 aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices);

	if (!imported_scene) {
		std::cerr << "failed to load scene/model with path: " << path << std::endl;
		return nullptr;
	}

	SceneNode* scene_node = scene.Add_Scene_Node(SceneNode(&scene)); 

	scene.transform_manager.Add_Component(scene_node->actor); 
	
	scene.model_manager.Add_Component(scene_node->actor); 

	std::vector<Mesh> meshes = Process_Meshes();
	scene_node->actor->Get_Component<Model>()->meshes = meshes; 

	return scene_node; 
}

Texture* Loader::Load_Texture(const std::string& path)
{
	auto iter = std::find_if(textures.begin(), textures.end(), [&path](std::pair<std::string, Texture> const& elem) { return elem.first == path; });

	if (iter != textures.end()) 
	{
		return &(iter->second); 
	}

	Texture texture; 
	if (texture.Init(Type::Texture, path)) 
	{
		textures.push_back({path, std::move(texture)});
		return &textures.back().second; 
	}

	return nullptr; 

}


std::vector<Mesh> Loader::Process_Meshes()
{
	std::vector<Mesh> meshes;

	meshes.resize(imported_scene->mNumMeshes);
	for (int i = 0; i < imported_scene->mNumMeshes; ++i)
	{
		aiMesh* curr_mesh = imported_scene->mMeshes[i];

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uv_coords;
		std::vector<glm::vec3> tangents; 
		std::vector<unsigned int> indices;

		positions.resize(curr_mesh->mNumVertices);
		for (int j = 0; j < curr_mesh->mNumVertices; ++j)
		{
			positions[j] = glm::vec3(curr_mesh->mVertices[j].x, curr_mesh->mVertices[j].y, curr_mesh->mVertices[j].z);
		}

		if (curr_mesh->HasNormals())
		{
			normals.resize(curr_mesh->mNumVertices);
			for (int j = 0; j < curr_mesh->mNumVertices; ++j)
			{
				normals[j] = glm::vec3(curr_mesh->mNormals[j].x, curr_mesh->mNormals[j].y, curr_mesh->mNormals[j].z);
			}
		}
		
		if (curr_mesh->HasTextureCoords(0))
		{
			uv_coords.resize(curr_mesh->mNumVertices);
			for (int j = 0; j < curr_mesh->mNumVertices; ++j)
			{
				uv_coords[j] = glm::vec2(curr_mesh->mTextureCoords[0][j].x, curr_mesh->mTextureCoords[0][j].y);
			}
		}
		
		if (curr_mesh->HasTangentsAndBitangents()) 
		{
			tangents.resize(curr_mesh->mNumVertices);
			for (int j = 0; j < curr_mesh->mNumVertices; ++j) 
			{
				tangents[j] = glm::vec3(curr_mesh->mTangents[j].x, curr_mesh->mTangents[j].y, curr_mesh->mTangents[j].z);
			}
		}

		indices.resize(curr_mesh->mNumFaces * 3);
		for (int j = 0; j < curr_mesh->mNumFaces; ++j)
		{
			indices[(j * 3)] = curr_mesh->mFaces[j].mIndices[0];
			indices[(j * 3) + 1] = curr_mesh->mFaces[j].mIndices[1];
			indices[(j * 3) + 2] = curr_mesh->mFaces[j].mIndices[2];
		}

		Mesh mesh(positions, normals, uv_coords, tangents, indices); 
		mesh.material.albedo_map = Load_Texture("Models/diffuse.jpg"); 
		mesh.material.normal_map = Load_Texture("Models/normal.png"); 

		meshes[i] = std::move(mesh);
	}

	return meshes;
}

SceneNode* Loader::Process_Node(const aiNode* node, Scene& scene)
{
	return nullptr; 
}
