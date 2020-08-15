#ifndef DUMMYGAME_H
#define DUMMYGAME_H

#include "IGame.h"
#include <iostream>
#include <functional>
#include "engine/shaders/ShaderProgram.h"
#include <Texture.h>

#define LOG(x) std::cout << x << std::endl;

class DummyGame : public Extonic::IGame
{
public:
	virtual void onInit();
	virtual void onUpdate(float delta);
	virtual void onRender();
	~DummyGame();
private:
	Extonic::ShaderProgram* program;
	void setupAttribs();
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int vertexColorLoc;
	Extonic::Texture texture;

	void createMesh();
	void createTexture();
};

#endif