#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/stb_image/stb_image.h"

#include <glew.h>
#include <iostream>

bool Texture::Init(const Type& type, std::string path)
{	
	
	switch (type)
	{
	case Type::Texture: 
		{
			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			
			stbi_set_flip_vertically_on_load(true);

			int channels, format = GL_RGB;

			unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			
			if (!data)
			{
				std::cerr << "Failed to load texture with path: " << path;
				return false;
			}

			if (channels == 4) format = GL_RGBA; 

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			stbi_image_free(data);
			
			Un_Bind(); 
		}
	break;

	case Type::ColorAttachmentRGB:
	{

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		
		Un_Bind(); 
	}
	break;

	case Type::ColorAttachmentRGB16bit:
	{
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

		Un_Bind();
	}
	break; 
}

	return true; 
}

void Texture::Create_Cube_Map(const std::vector<std::string>& paths)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	//stbi_set_flip_vertically_on_load(true);

	int width, height, channels, format = GL_RGB;

	for (int i = 0; i < paths.size(); ++i) 
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			std::cerr << "Failed to load face with path: " << paths[i];
			stbi_image_free(data);
		}
		
		if (channels == 4) 
		{
			format = GL_RGBA;
		} 

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		Un_Bind();
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::Bind(int id)
{
	glActiveTexture(GL_TEXTURE0 + id); 
	glBindTexture(GL_TEXTURE_2D, texture_id); 
}

void Texture::Un_Bind()
{
	glBindTexture(GL_TEXTURE_2D, 0); 
}

void Texture::Clear()
{
	glDeleteTextures(1, &texture_id); 
}
