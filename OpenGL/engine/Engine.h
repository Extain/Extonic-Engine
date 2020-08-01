#pragma once
#include "Window.h"
#include <chrono>


class Engine {
public:
	Engine(const char* title, int width, int height);
	void init();

private:
	~Engine();
	void loop();
	void update(float delta);
	void render();
	int ups;
	int fps;
	Window* window;
};