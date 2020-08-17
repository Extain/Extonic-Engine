#ifndef IGAME_H
#define IGAME_H

#include <GLFW/glfw3.h>


namespace Extonic {
	class IGame
	{
	public:
		virtual void onInit(GLFWwindow *window) = 0;
		virtual void processInput(GLFWwindow* window) = 0;
		virtual void onUpdate(float delta) = 0;
		virtual void onRender() = 0;
	};
}

#endif