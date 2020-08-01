#include "Engine.h"

Engine::Engine(std::string title, uint32_t width, uint32_t height)
{
	window = new Window(title, width, height);
}

void Engine::init()
{
}

Engine::~Engine()
{

}