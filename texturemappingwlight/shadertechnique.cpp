#include "shadertechnique.h"
#include "uniformvariables.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

void buildShaders()
{
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0)
    {
        std::cerr << "Error creating shader program\n";
        exit(1);
    }

    std::string VS = readFileToString("vertexShader.glsl");
    std::string FS = readFileToString("fragmentShader.glsl");

    addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error linking shader program: " << errorLog << std::endl;
        exit(1);
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error linking shader program: " << errorLog << std::endl;
        exit(1);
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLoc = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLoc != 0xFFFFFFFF);
    gWorldToViewToProjectionTransformLoc = glGetUniformLocation(shaderProgram, "gWorldToViewToProjectionTransform");
    assert(gWorldToViewToProjectionTransformLoc != 0xFFFFFFFF);
    gAmbientLightIntensityLoc = glGetUniformLocation(shaderProgram, "gAmbientLightIntensity");
    assert(gAmbientLightIntensityLoc != 0xFFFFFFFF);
    gDirectionalLightIntensityLoc = glGetUniformLocation(shaderProgram, "gDirectionalLightIntensity");
    assert(gDirectionalLightIntensityLoc != 0xFFFFFFFF);
    gDirectionalLightDirectionLoc = glGetUniformLocation(shaderProgram, "gDirectionalLightDirection");
    assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);
    gKaLoc = glGetUniformLocation(shaderProgram, "gKa");
    assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);
    gKdLoc = glGetUniformLocation(shaderProgram, "gKd");
    assert(gDirectionalLightDirectionLoc != 0xFFFFFFFF);
    gTextureSamplerLoc = glGetUniformLocation(shaderProgram, "gTextureSampler");
    assert(gTextureSamplerLoc != 0xFFFFFFFF);
}

void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0)
    {
        std::cerr << "Error creating shader type " << shaderType << std::endl;
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0] = strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        std::cerr << "Error compiling shader type " << shaderType << ": " << InfoLog << std::endl;
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObj);
}

const std::string readFileToString(const char* filename)
{
    std::ifstream file(filename, std::ios::in);
    if (file.is_open())
    {
        std::stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
        return continut.str();
    }
    return "";
}