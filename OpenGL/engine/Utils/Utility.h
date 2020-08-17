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

        const char* loadShader(const char* path)
        {
            std::string shaderCode;
            std::ifstream shaderFile;

            shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                shaderFile.open(path);
                std::stringstream shaderStream;

                shaderStream << shaderFile.rdbuf();

                shaderFile.close();

                shaderCode = shaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
            }

            return shaderCode.c_str();
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