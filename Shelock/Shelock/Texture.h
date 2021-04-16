#pragma once

#include <vector>
#include <string>

enum class Type 
{
	Texture,
	ColorAttachment
};


class Texture
{
public:

	bool Init(const Type& type, std::string path = "");
	void Create_Cube_Map(const std::vector<std::string>& paths); 
	
	void Bind(int id); 
	void Un_Bind(); 
	void Clear(); 

	int width = 0; 
	int height = 0;

	unsigned int texture_id; 

};

