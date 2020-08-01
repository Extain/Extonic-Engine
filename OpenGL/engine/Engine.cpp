#include "Engine.h"
#include <iostream>


using namespace std::chrono_literals;

Engine::Engine(const char *title, int width, int height)
{
	window = new Window(title, width, height);
}

void Engine::init()
{

	loop();
}

void Engine::loop()
{

	double timeDelta = 1 / 60;
	double accumulator = 0;

	while (!window->shouldClose())
	{
		double now = 0;
		auto startTime = glfwGetTime();

		if (accumulator >= timeDelta)
		{
			update(timeDelta);
			accumulator -= timeDelta;
			now += timeDelta;
		}

		render();

		accumulator += glfwGetTime() - startTime;
	}
}

void Engine::update(float delta)
{
	window->update();
}

void Engine::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	// Render game stuff

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	window->swapBuffers();
}

Engine::~Engine()
{

}