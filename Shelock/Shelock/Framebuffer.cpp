#include "Framebuffer.h"

#include <glew.h>
#include <iostream>

Framebuffer::Framebuffer():
	framebuffer_id(0),
	depth_buffer_id(0)
{
}

bool Framebuffer::Create_Framebuffer(const Layout& layout)
{
	color_attachments.resize(MAX_COLOR_ATTACHMENTS);

	if (layout == Layout::ColorDepth)
	{

		glGenFramebuffers(1, &framebuffer_id);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

		glGenTextures(1, &color_attachments[0]);
		glBindTexture(GL_TEXTURE_2D, color_attachments[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachments[0], 0);
		glBindTexture(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0);

		glGenTextures(1, &depth_buffer_id);
		glBindTexture(GL_TEXTURE_2D, depth_buffer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1280, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_buffer_id, 0);
		glBindTexture(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	return true;
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id); 
}

void Framebuffer::Un_Bind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &framebuffer_id);
}
