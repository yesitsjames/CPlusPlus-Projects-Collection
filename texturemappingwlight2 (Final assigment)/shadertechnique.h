#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

using namespace glm;

class ShaderTechnique
{
private:
    GLuint shaderProgram;
    GLuint loadShader(const char* shaderPath, GLenum shaderType);
    std::string readFile(const char* filePath);
    void AddShader(const char* pShaderText, GLenum shaderType);
    std::string ReadFileToString(const char* filename);

public:
    void loadShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
    GLuint getShaderProgram() const { return shaderProgram; }
};