#pragma once
#include <cstdint>
#include <string>
#include <glad\gl.h>
#include <GLFW\glfw3.h>

namespace Extonic {
	class Window {
	public:

		Window(const char* title, int width, int height);

		virtual int& getWidth() { return _width; }
		virtual int& getHeight() { return _height; }
		virtual const char& getTitle() { return *_title; }
		virtual GLFWwindow& getWindowHandle() { return *windowHandle; }

		void update();
		void swapBuffers();
		bool shouldClose();
	private:
		void onResize(int width, int height);
		int createWindow();
		const char* _title;
		int _width;
		int _height;
		GLFWwindow* windowHandle;
	};
}
