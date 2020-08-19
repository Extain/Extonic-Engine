#ifndef UTILITY_H
#define UTILITY_H

#include <fstream>
#include <string>
#include <time.h>
#include <sstream>

#include <iostream>

namespace Extonic {
    class Util
    {
    public:
        static std::string loadFileAsString(std::string filePath);
        static const char* loadShader(const char* path);
    };
}
#endif