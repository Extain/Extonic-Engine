#pragma once

#include <glad/gl.h>

namespace Extonic {
	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height)
		{
			this->width = width;
			this->height = height;

		}
		void bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fboID);
		}
		void unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void resize(int width, int height)
		{
			this->width = width;
			this->height = height;
		}

	private:
		unsigned int fboID;
		unsigned int texID;
		unsigned int rboID;

		void createBuffer()
		{
			glGenFramebuffers(1, &fboID);

			glBindFramebuffer(GL_FRAMEBUFFER, fboID);

			glGenTextures(1, &texID);
			glBindTexture(GL_TEXTURE_2D, texID);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		int width, height;
	};
}