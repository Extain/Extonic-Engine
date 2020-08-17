#ifndef DUMMYGAME_H
#define DUMMYGAME_H

#include "engine/shaders/ShaderProgram.h"
#include "IGame.h"
#include <iostream>
#include <functional>
#include <Texture.h>
#include <GLFW\glfw3.h>
#include <Camera.h>

#define LOG(x) std::cout << x << std::endl;

class DummyGame : public Extonic::IGame
{
public:
	virtual void onInit(GLFWwindow *window);
	virtual void processInput(GLFWwindow* window);
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

	static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void createMesh();
	void createTexture();
};

#endif