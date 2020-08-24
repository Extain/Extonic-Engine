#ifndef DUMMYGAME_H
#define DUMMYGAME_H

#include <glad/gl.h>
#include <IGame.h>
#include <engine\Engine.h>
#include <functional>
#include <engine\graphics\Texture.h>
#include <engine\shaders\LightShader.h>
#include <engine\camera\PerspectiveCamera.h>
#include <entt.hpp> 
#include <Input.h>

#define LOG(x) std::cout << x << std::endl;

class DummyGame : public Extonic::IGame
{
public:
	virtual void onInit(GLFWwindow *window);
	virtual void onUpdate(float delta);
	virtual void onRender();
	~DummyGame();
private:
	//Extonic::ShaderProgram* program;
	void setupAttribs();
	unsigned int lightVAO;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int vertexColorLoc;
	Extonic::Texture texture;

	static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void setupLights();
	void createMesh();
	void createTexture();
	entt::registry m_Registry;
};
#endif