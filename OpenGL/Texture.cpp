#include "Texture.h"

namespace Extonic {
	void Texture::createTexture(const char* fileName)
	{
		glGenTextures(1, &textureID);
		LOG("Generating Textures ID: ", textureID);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		unsigned char* data = stbi_load(fileName, &width, &height, &nrChannel, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LOG("Failed to load texture", fileName);
		}

		stbi_image_free(data);
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
