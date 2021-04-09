#pragma once


#define MAX_COLOR_ATTACHMENTS 4

#include <vector>

enum class Layout 
{
	ColorDepth
};

class Framebuffer
{
public:

	Framebuffer(); 

	bool Create_Framebuffer(const Layout& layout);

	void Bind(); 
	void Un_Bind(); 

	~Framebuffer(); 
	
	unsigned int framebuffer_id;
	unsigned int depth_buffer_id; 
	std::vector<unsigned int> color_attachments; 
};

