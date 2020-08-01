#include "Window.h"

#include <glad/gl.h>

#include <GLFW/glfw3.h>

Window::Window(std::string title, uint32_t width, uint32_t height)
{
	this->title = title;
	this->_width = width;
	this->_height = height;

	//createWindow();
}

void createWindow() 
{

}
