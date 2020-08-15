#pragma once
#include <iostream>
#include <map>
#include <string>
#include <glad\gl.h>
#include <ext\vector_float4.hpp>
#include <mat4x4.hpp>


namespace Extonic {
    class ShaderProgram
    {
    public:
        int shaderID;
        ShaderProgram();

        virtual void use() { glUseProgram(shaderID); }
        virtual void unbind() { glUseProgram(0); }

        void uniform4f(const std::string &uniform, glm::vec4 &value);
        void uniform4f(const std::string& uniform, float x, float y, float z, float a);
        void matrix4f(const std::string& uniform, glm::mat4x4 &value);

        void createShader(const char* vs, const char* fs);
        void createDefaultShader();
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

        std::string vertexShader;
        std::string fragmentShader;
        std::map<std::string, int> uniforms;
    };
}
