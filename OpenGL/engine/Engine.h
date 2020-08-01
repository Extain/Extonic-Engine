#pragma once
#include "Window.h"

class Engine {
public:
	void init();

private:
	Engine(std::string title, uint32_t width, uint32_t height);
	~Engine();
	bool isRunning;
	int ups;
	int fps;
	Window* window;
};