// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "engine/Engine.h"
#include "DummyGame.h"





int main()
{
    DummyGame game;
    Extonic::Engine* engine = new Extonic::Engine(game, "Testing", 800, 600);
    engine->init();

    

    return 0;
}
