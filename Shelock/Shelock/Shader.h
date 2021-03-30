#pragma once

#include <string>

class Shader
{
public:
	Shader(); 


	void Create_Shader_Program(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	unsigned int& Get_Shader_program() { return shader_program_id; }

	void Bind();

	~Shader(); 

private:
	std::string Parse_Source(const std::string& path);
	unsigned int Compile(unsigned int type, const std::string source);

private:
	unsigned int shader_program_id; 
};

