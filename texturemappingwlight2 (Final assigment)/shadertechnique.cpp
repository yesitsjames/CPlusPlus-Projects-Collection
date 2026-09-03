#include "ShaderTechnique.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

std::string ShaderTechnique::readFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string ShaderTechnique::ReadFileToString(const char* filename) {
    return readFile(filename); 
}

GLuint ShaderTechnique::loadShader(const char* shaderPath, GLenum shaderType) {
    std::string shaderCode = readFile(shaderPath);
    const char* shaderSource = shaderCode.c_str();

    GLuint shaderObj = glCreateShader(shaderType);
    glShaderSource(shaderObj, 1, &shaderSource, nullptr);
    glCompileShader(shaderObj);

    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shaderObj, sizeof(log), nullptr, log);
        std::cerr << "Error compiling shader: " << log << std::endl;
        assert(false);
    }

    return shaderObj;
}

void ShaderTechnique::AddShader(const char* pShaderText, GLenum shaderType) {
    GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) {
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
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        std::cerr << "Error compiling shader type " << shaderType << ": " << InfoLog << std::endl;
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObj);
}


void ShaderTechnique::loadShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    shaderProgram = glCreateProgram();

    std::string VS = ReadFileToString(vertexShaderPath);
    std::string FS = ReadFileToString(fragmentShaderPath);

    AddShader(VS.c_str(), GL_VERTEX_SHADER);
    AddShader(FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error linking shader program: " << errorLog << std::endl;
        exit(1);
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::cerr << "Error validating shader program: " << errorLog << std::endl;
        exit(1);
    }

    glUseProgram(shaderProgram);
}

/* 
* 
Pre encapsulation and assigning sections to other classes to actually get it to work-


#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include "aiterror.h"
#include "ShaderProgram.h"
#include <string>

using namespace std;

void ShaderAdd::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    cout << "shaders being Added";
    GLuint shaderObj = glCreateShader(shaderType);
    if (shaderObj == 0)
    {
        std::stringstream ss;
        ss << "Error creating shader type " << shaderType << endl;
        AIT_ASSERT(0, ss.str());
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
        std::stringstream ss;
        ss << "Error compiling shader type " << shaderType << ": " << InfoLog << endl;
        AIT_ASSERT(0, ss.str());
    }
    glAttachShader(shaderProgram, shaderObj);
}

const string ShaderAdd::readFileToString(char* filename)
{
    std::cout << "Attempting to read file: " << filename << std::endl;
    ifstream file(filename, ios::in);
    if (file.is_open())
    {
        std::cout << "Successfully opened file: " << filename << std::endl;
        stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
        return continut.str();
    }
    std::cerr << "ERROR: File not found: " << filename << std::endl;
    AIT_ASSERT(0, "File not found: " + std::string(filename));
    return "";
}

void ShaderAdd::buildShaders(char* vsfn, char* fsfn)
{
    sp = glCreateProgram(); // Create a shader program
    if (sp == 0)
    {
        AIT_ASSERT(0, "Error creating shader program\n");
    }
    string VS = readFileToString(vsfn);  // Read vertex shader file
    string FS = readFileToString(fsfn);  // Read fragment shader file
    addShader(sp, VS.c_str(), GL_VERTEX_SHADER);
    addShader(sp, FS.c_str(), GL_FRAGMENT_SHADER);
    GLint success = 0;
    GLchar errorLog[1024] = { 0 };
    glLinkProgram(sp);
    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(sp, sizeof(errorLog), NULL, errorLog);
        AIT_ASSERT(0, string("Error linking shader program: ") + errorLog);
    }
    glValidateProgram(sp);
    glGetProgramiv(sp, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(sp, sizeof(errorLog), NULL, errorLog);
        AIT_ASSERT(0, string("Error validating shader program: ") + errorLog);
    }

    // Get uniform locations
    modelLocation = glGetUniformLocation(sp, "model");
    viewLocation = glGetUniformLocation(sp, "view");
    projectionLocation = glGetUniformLocation(sp, "projection");
}

void ShaderAdd::use()
{
    std::cout << "Using shader program: " << sp << std::endl;
    if (sp == 0)
    {
        std::cerr << "Error: Shader program not built yet!" << std::endl;
        return;
    }
    glUseProgram(sp);
}

GLuint ShaderAdd::getShaderProgram()
{
    return sp;
}

GLuint ShaderAdd::getUniformLocation(const char* name) const
{
    return glGetUniformLocation(sp, name);
}

// Matrix setter methods - these were missing in your implementation
void ShaderAdd::setModelMatrix(const glm::mat4& model)
{
    if (sp == 0) return;

    // Use the cached uniform location if available
    if (modelLocation != 0) {
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    }

}

void ShaderAdd::setViewMatrix(const glm::mat4& view)
{
    if (sp == 0) return;

    // Use the cached uniform location if available
    if (viewLocation != 0) {
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    }

}

void ShaderAdd::setProjectionMatrix(const glm::mat4& projection)
{
    if (sp == 0) return;

    // Use the cached uniform location if available
    if (projectionLocation != 0) {
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }
    else {
        // Look up the location if not cached yet
        GLuint loc = glGetUniformLocation(sp, "projection");
        if (loc != -1) {
            projectionLocation = loc; // Cache for future use
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
        }
    }
}

*/