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

	unsigned int& Get_Framebuffer_Id() { return framebuffer_id; }
	unsigned int& Get_Depth_Buffer_Id() { return depth_buffer_id; }
	std::vector<unsigned int>& Get_Color_Attachments() { return color_attachments; }


	~Framebuffer(); 

private:
	unsigned int framebuffer_id;
	unsigned int depth_buffer_id; 
	std::vector<unsigned int> color_attachments; 
};

