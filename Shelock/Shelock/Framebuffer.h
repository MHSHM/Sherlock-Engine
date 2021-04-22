#pragma once


#define MAX_COLOR_ATTACHMENTS 4

#include "Texture.h"

#include <vector>

enum class Layout 
{
	ColorDepth,
	Color16fDepth,
	Color32fDepth
};

class Framebuffer
{
public:

	Framebuffer(); 

	bool Init(const Layout& layout);

	void Bind(); 
	void Un_Bind(); 

	~Framebuffer(); 
	
	unsigned int framebuffer_id;
	unsigned int depth_buffer_id; 
	std::vector<Texture> color_attachments; 
};

