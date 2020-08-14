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
		this->game.onInit();
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
				accumulator -= timeDelta;
				update(timeDelta);
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