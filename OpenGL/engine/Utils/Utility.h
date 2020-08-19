#pragma once
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace Extonic {
    namespace Util
    {
        std::string loadFileAsString(std::string filePath)
        {
            std::ifstream ifs(filePath);
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            return content;
        }

        std::string loadShader(const char* path)
        {
            std::string shader;
            std::ifstream shaderFile;
            try
            {
                shaderFile.open(path, std::ios::in);
                std::stringstream shaderStream;

                shaderStream << shaderFile.rdbuf();

                std::cout << shaderStream.str() << std::endl;

                shaderFile.close();

                shader = shaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
            }

            return shader;
        }

        // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
        const std::string CurrentDateTime()
        {
            time_t     now = time(NULL);
            struct tm  tstruct;
            char       buf[80];
            localtime_s(&tstruct, &now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
            return buf;
        }
    };
}