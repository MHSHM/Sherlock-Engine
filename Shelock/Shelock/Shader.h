#pragma once

#include <string>

#include "../Dependencies/GLM/mat4x4.hpp"
#include "../Dependencies/GLM/gtc/type_ptr.hpp"


class Shader
{
public:
	Shader(); 


	void Create_Shader_Program(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	unsigned int& Get_Shader_program() { return shader_program_id; }

	void Set_Matrix4_Uniform(std::string uniform, glm::mat4& matrix);
	void Set_Vec3_Uniform(std::string uniform, glm::vec3 vector); 
	void Set_Float_Uniform(std::string uniform, float val); 
	void Set_Int_Uniform(std::string uniform, int val); 

	void Bind();

	~Shader(); 

private:
	std::string Parse_Source(const std::string& path);
	unsigned int Compile(unsigned int type, const std::string source);

private:
	unsigned int shader_program_id; 
};

