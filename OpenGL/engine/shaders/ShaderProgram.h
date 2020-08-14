#pragma once
#include <iostream>
#include <string>
#include <glad\gl.h>


namespace Extonic {
    class ShaderProgram
    {
    public:
        int shaderID;
        ShaderProgram();

        virtual void use() { glUseProgram(shaderID); }
        virtual void unbind() { glUseProgram(0); }

        ~ShaderProgram();
    private:
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec4 aColor;\n"
            "out vec4 ourColor;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos, 1.0);\n"
            "   ourColor = aColor;\n"
            "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec4 ourColor;\n"
            "uniform vec4 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = color;\n"
            "}\n\0";

        void loadShader();
        std::string vertexShader;
        std::string fragmentShader;
    };
}
