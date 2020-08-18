#include "Texture.h"

namespace Extonic {
	void Texture::createTexture(const char* fileName)
	{
		glGenTextures(1, &textureID);
		LOG("Generating Textures ID: ", textureID);
		bind();

		unsigned char* data = stbi_load(fileName, &width, &height, &nrChannel, 0);

		if (data)
		{
			GLenum format;
			if (nrChannel == 1)
				format = GL_RED;
			else if (nrChannel == 3)
				format = GL_RGB;
			else if (nrChannel == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			LOG("Failed to load texture", fileName);
			stbi_image_free(data);
		}
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
