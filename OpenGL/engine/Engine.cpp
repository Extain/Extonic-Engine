#include "Engine.h"
#include <iostream>

using namespace std::chrono_literals;

namespace Extonic {
	Engine::Engine(IGame& gme, const char* title, int width, int height) : game(gme)
	{
		window = new Window(title, width, height);
	}

	void Engine::init()
	{
		this->game.onInit(&window->getWindowHandle());
		loop();
	}

	void Engine::loop()
	{

		double timeDelta = 1 / 60;
		float deltaTime = 0;
		float lastTime = 0;
		double accumulator = 0;

		while (!window->shouldClose())
		{
			double now = 0;
			auto startTime = glfwGetTime();

			if (accumulator >= timeDelta)
			{
				accumulator -= timeDelta;
				deltaTime = startTime - lastTime;
				update(deltaTime);
				lastTime = startTime;
				now += timeDelta;
			}

			render();

			accumulator += glfwGetTime() - startTime;
		}
	}

	void Engine::update(float delta)
	{
		window->update();
		this->game.onUpdate(delta);
	}

	void Engine::render()
	{
		this->game.onRender();

		window->swapBuffers();
	}

	Engine::~Engine()
	{

	}
}