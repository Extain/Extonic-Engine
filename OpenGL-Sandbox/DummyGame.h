#ifndef DUMMYGAME_H
#define DUMMYGAME_H

#include "IGame.h"
#include <iostream>
#include <functional>
#include "engine/shaders/ShaderProgram.h"

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
};

#endif