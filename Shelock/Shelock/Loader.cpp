#include "Loader.h"
#include "Scene.h"


SceneNode* Loader::Load(Scene& scene, const std::string& path)
{
	Assimp::Importer importer;

	const aiScene* imported_scene = importer.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices);

	if (!imported_scene) {
		std::cerr << "failed to load scene/model with path: " << path << std::endl;
		return nullptr;
	}

	scene_root = imported_scene->mRootNode;
	scene_meshes = imported_scene->mMeshes;
	scene_materials = imported_scene->mMaterials;

	return Process_Node(scene_root, scene);
}

SceneNode* Loader::Process_Node(const aiNode* node, Scene& scene)
{

	SceneNode* scene_node = scene.Add_Scene_Node(SceneNode(&scene)); 
	
	scene_node->Get_Actor()->Add_Component(ComponentType::TransformComp); 
	
	scene_node->Get_Actor()->Add_Component(ComponentType::ModelComp); 
	std::vector<Mesh> meshes = Process_Meshes(node);
	scene_node->Get_Actor()->Get_Model_Component()->Set_Meshes(meshes); 
	
	return scene_node; 
}

std::vector<Mesh> Loader::Process_Meshes(const aiNode* node)
{
	std::vector<Mesh> meshes;

	meshes.resize(node->mNumMeshes); 
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* curr_mesh = scene_meshes[node->mMeshes[i]];

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uv_coords;
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
				uv_coords[j] = glm::vec2(curr_mesh->mTextureCoords[j][0].x, curr_mesh->mTextureCoords[j][0].y);
			}
		}

		indices.resize(curr_mesh->mNumFaces * 3);
		for (int j = 0; j < curr_mesh->mNumFaces; ++j)
		{
			indices[(j * 3)] = curr_mesh->mFaces[j].mIndices[0];
			indices[(j * 3) + 1] = curr_mesh->mFaces[j].mIndices[1];
			indices[(j * 3) + 2] = curr_mesh->mFaces[j].mIndices[2];
		}

		meshes[i] = std::move(Mesh(positions, normals, uv_coords, indices));
	}

	return meshes;
}