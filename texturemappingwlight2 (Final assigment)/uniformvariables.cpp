#include "UniformVariables.h"
#include <cassert>
#include <iostream>

UniformVariables::UniformVariables() : 
    //initalising all to 0
    programID(0),
    modelToWorldTransform(0),
    worldToViewToProjectionTransform(0),
    ambientLightIntensity(0),
    directionalLightIntensity(0),
    directionalLightDirection(0),
    ka(0),
    kd(0),
    textureSampler(0)
{
}

void UniformVariables::Init(GLuint shaderProgram)
{
    programID = shaderProgram;

    // transforms
    modelToWorldTransform = glGetUniformLocation(programID, "gModelToWorldTransform");
    if (modelToWorldTransform == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gModelToWorldTransform' not found in shader program." << std::endl;
    }

    worldToViewToProjectionTransform = glGetUniformLocation(programID, "gWorldToViewToProjectionTransform");
    if (worldToViewToProjectionTransform == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gWorldToViewToProjectionTransform' not found in shader program." << std::endl;
    }

    // lighting
    ambientLightIntensity = glGetUniformLocation(programID, "gAmbientLightIntensity");
    if (ambientLightIntensity == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gAmbientLightIntensity' not found in shader program." << std::endl;
    }

    directionalLightIntensity = glGetUniformLocation(programID, "gDirectionalLightIntensity");
    if (directionalLightIntensity == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gDirectionalLightIntensity' not found in shader program." << std::endl;
    }

    directionalLightDirection = glGetUniformLocation(programID, "gDirectionalLightDirection");
    if (directionalLightDirection == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gDirectionalLightDirection' not found in shader program." << std::endl;
    }

    // materials
    ka = glGetUniformLocation(programID, "gKa");
    if (ka == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gKa' not found in shader program." << std::endl;
    }

    kd = glGetUniformLocation(programID, "gKd");
    if (kd == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gKd' not found in shader program." << std::endl;
    }

    // Get uniform location for texture
    textureSampler = glGetUniformLocation(programID, "gTextureSampler");
    if (textureSampler == 0xFFFFFFFF) {
        std::cerr << "Warning: Uniform 'gTextureSampler' not found in shader program." << std::endl;
    }
}



//repeating gluints (debugging mess - gonna relook over)

GLuint UniformVariables::GetModelToWorldTransformLocation() const
{
    return modelToWorldTransform;
}

GLuint UniformVariables::GetWorldToViewToProjectionTransformLocation() const
{
    return worldToViewToProjectionTransform;
}

GLuint UniformVariables::GetAmbientLightIntensityLocation() const
{
    return ambientLightIntensity;
}

GLuint UniformVariables::GetDirectionalLightIntensityLocation() const
{
    return directionalLightIntensity;
}

GLuint UniformVariables::GetDirectionalLightDirectionLocation() const
{
    return directionalLightDirection;
}

GLuint UniformVariables::GetKaLocation() const
{
    return ka;
}

GLuint UniformVariables::GetKdLocation() const
{
    return kd;
}

GLuint UniformVariables::GetTextureSamplerLocation() const
{
    return textureSampler;
}