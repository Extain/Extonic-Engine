#ifndef INPUT_H
#define INPUT_H

#include <GLFW\glfw3.h>
#include "engine/Window.h"

namespace Extonic {
	class Input
	{
	public:
		static bool isKeyPressed(int key)
		{
			auto window = static_cast<GLFWwindow*>(&Window::Get().getWindowHandle());
			auto state = glfwGetKey(window, static_cast<int32_t>(key));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		static bool IsMouseButtonPressed(int button)
		{
			auto window = static_cast<GLFWwindow*>(&Window::Get().getWindowHandle());
			auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}

		static std::pair<float, float> GetMousePosition()
		{
			auto window = static_cast<GLFWwindow*>(&Window::Get().getWindowHandle());
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			return { (float)xpos, (float)ypos };
		}

		static float GetMouseX()
		{
			return GetMousePosition().first;
		}

		static float GetMouseY()
		{
			return GetMousePosition().second;
		}
	};
}
#endif