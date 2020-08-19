#ifndef ENGINE_H
#define ENGINE_H
#include "Window.h"
#include "../IGame.h"
#include <chrono>


namespace Extonic {
	class Engine {
	public:
		Engine(IGame& game, const char* title, int width, int height);
		void init();
		virtual void setGame(const IGame& gme) { this->game = gme; }

	private:
		~Engine();
		void loop();
		void update(float delta);
		void render();
		IGame& game;
		int ups;
		int fps;
		Window* window;
	};
}
#endif