#ifndef IGAME_H
#define IGAME_H

#include <iostream>


namespace Extonic {
	class IGame
	{
	public:
		virtual void onInit() = 0;
		virtual void onUpdate(float delta) = 0;
		virtual void onRender() = 0;
	};
}

#endif