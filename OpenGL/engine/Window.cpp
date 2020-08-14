#include "Window.h"
#include <iostream>

namespace Extonic {
    Window::Window(const char* title, int width, int height)
    {
        this->_title = title;
        this->_width = width;
        this->_height = height;

        createWindow();
    }

    int Window::createWindow()
    {
        GLFWwindow* window;

        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        window = glfwCreateWindow(this->getWidth(), this->getHeight(), _title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            std::cout << "Resized Window" << std::endl;
            glViewport(0, 0, width, height);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            switch (action)
            {
            case GLFW_PRESS:
                if (key == GLFW_KEY_ESCAPE)
                {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
            }
        });

        glfwMakeContextCurrent(window);

        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            printf("Failed to initialize OpenGL context\n");
            return -1;
        }

        this->windowHandle = window;

        glViewport(0, 0, _width, _height);
    }

    void Window::onResize(int width, int height)
    {
        _width = width;
        _height = height;
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(windowHandle);
    }

    void Window::update()
    {
        glfwPollEvents();
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(windowHandle);
    }
}
