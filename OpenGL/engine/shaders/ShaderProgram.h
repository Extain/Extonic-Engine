#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>
#include <map>
#include <string>
#include <ext\vector_float4.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glad\gl.h>


namespace Extonic {
    class ShaderProgram
    {
    public:
        int shaderID;
        ShaderProgram();

        virtual void use() { glUseProgram(shaderID); }
        virtual void unbind() { glUseProgram(0); }

        void uniform1i(const std::string& uniform, int value);
        void uniform4f(const std::string &uniform, glm::vec4 &value);
        void uniform4f(const std::string& uniform, float x, float y, float z, float a);
        void matrix4f(const std::string& uniform, glm::mat4 &value);
        void uniform3f(const std::string& uniform, glm::vec3& value);
        void uniform3f(const std::string& uniform, float x, float y, float z);
        void uniform1f(const std::string& uniform, float value);

        void createShader(const char* vs, const char* fs);
        void createDefaultShader();
        ~ShaderProgram();
    private:
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos; \n"
            "layout (location = 1) in vec4 aColor; \n"
            "layout (location = 2) in vec2 aTexCoord; \n"
            "out vec4 ourColor; \n"
            "out vec2 TexCoord; \n"
            "uniform mat4 model; \n"
            "uniform mat4 view; \n"
            "uniform mat4 projection; \n"
            "void main()\n"
            "{\n"
            "   gl_Position = projection * view * model * vec4(aPos, 1.0); \n"
            "   ourColor = aColor; \n"
            "   TexCoord = aTexCoord; \n"
            "}\0";

        const char* fragmentShaderSource = "#version 330 core \n"
            "out vec4 FragColor; \n"
            "in vec4 ourColor; \n"
            "in vec2 TexCoord; \n"
            "uniform vec4 color; \n"
            "uniform sampler2D ourTexture; \n"
            "void main() \n"
            "{ \n"
            "   FragColor = texture(ourTexture, TexCoord) * color; \n"
            "} \n\0";

        std::string vertexShader;
        std::string fragmentShader;
        std::map<std::string, int> uniforms;
    };
}
#endif
