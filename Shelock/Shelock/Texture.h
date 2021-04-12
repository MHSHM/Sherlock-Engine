#pragma once

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
	void Bind(int id); 
	void Un_Bind(); 
	void Clear(); 

	int width; 
	int height; 
	unsigned int texture_id; 

};

