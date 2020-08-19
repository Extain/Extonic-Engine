#include "Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Extonic {

    std::string Util::loadFileAsString(std::string filePath)
    {
        std::ifstream ifs(filePath);
        std::string fileText;
        while (ifs.good())
        {
            std::string line;
            std::getline(ifs, line);
            fileText.append(line + "\n");
        }
        return fileText;
    }

    const char* Util::loadShader(const char* path)
    {
        std::string shader;
        std::ifstream shaderFile;
        std::stringstream shaderStream;
        try
        {
            shaderFile.open(path, std::ios::in);

            shaderStream << shaderFile.rdbuf();

            std::cout << shaderStream.str().c_str() << std::endl;

            shader = shaderStream.str();

            shaderFile.close();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
        }

        const char* shaderCode = shader.c_str();

        return shaderCode;
    }
}