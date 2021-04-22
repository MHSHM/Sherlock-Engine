#include "Framebuffer.h"
#include "Texture.h"

#include <glew.h>
#include <iostream>

Framebuffer::Framebuffer():
	framebuffer_id(0),
	depth_buffer_id(0)
{
}

bool Framebuffer::Init(const Layout& layout)
{
	color_attachments.reserve(MAX_COLOR_ATTACHMENTS);

	glGenFramebuffers(1, &framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

	switch (layout)
	{
		case Layout::ColorDepth: 
		{
			Texture color_attachment;
			color_attachment.width = 1280;
			color_attachment.height = 720;

			if (!color_attachment.Init(Type::ColorAttachmentRGB))
			{
				std::cerr << "Failed to create color attachment \n";
				return false;
			}

			color_attachments.push_back(std::move(color_attachment));

			glGenRenderbuffers(1, &depth_buffer_id);
			glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachments.back().texture_id, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				return false;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		break; 

		case Layout::Color16fDepth: 
		{
			Texture color_attachment;
			color_attachment.width = 1280;
			color_attachment.height = 720;

			if (!color_attachment.Init(Type::ColorAttachmentRGB16bit))
			{
				std::cerr << "Failed to create color attachment \n";
				return false;
			}

			color_attachments.push_back(std::move(color_attachment));

			glGenRenderbuffers(1, &depth_buffer_id);
			glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachments.back().texture_id, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				return false;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
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
	for (auto& texture : color_attachments) 
	{
		texture.Clear(); 
	}
}
