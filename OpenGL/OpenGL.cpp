// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "engine/Engine.h"





int main()
{
    Engine* engine = new Engine("Testing", 800, 600);

    engine->init();
    
    return 0;
}
