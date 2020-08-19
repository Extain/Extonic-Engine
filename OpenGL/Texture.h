#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>
#include <iostream>


#define LOG(x) std::cout << x << std::endl
#define LOG(x, y) std::cout << x << y << std::endl;

namespace Extonic {

	class Texture
	{
	public:
		void createTexture(const char* fileName);
		void bind();
		void unbind();

		unsigned int getID(){ return textureID; }
	private:
		unsigned int textureID;
		int width, height, nrChannel;

	};
}

#endif