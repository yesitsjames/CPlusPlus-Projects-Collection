#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>

#include "aiterror.h"

using namespace std;
using namespace glm;

GLuint VBO;
const int NUMVERTS = 3;

// Our simple vertex container
struct SimpleVertex
{
    glm::vec3		pos;	// Position
	glm::vec4		colour;	// Colour
	glm::vec3		normal; // Normal
};

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 40, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)12); //change values
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)28); //change values


    glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

static void createVertexBuffer()
{
	// Create some vertices to put in our VBO.
	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-0.5f, -0.5f, 0.0f)},
		{ glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) , glm::vec3(-0.5f, -0.5f, 0.0f) },
	{ glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) , glm::vec3(-0.5f, -0.5f, 0.0f)}
	};
    
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * 3, vertices, GL_STATIC_DRAW);
}

static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
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

const string readFileToString(char* filename)
{
	ifstream file(filename, ios::in);
	if (file.is_open())
	{
		stringstream continut;
		continut << file.rdbuf();
		continut << '\0';
		return continut.str();
	}
	AIT_ASSERT(0, "File not found!");
}

static void buildShaders()
{
   GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0) 
	{
		AIT_ASSERT(0, "Error creating shader program\n");
    }

	string VS = readFileToString("vertexShader.glsl");
	string FS = readFileToString("fragmentShader.glsl");

    addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) 
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::stringstream ss;
		ss<<"Error linking shader program: "<<errorLog<<std::endl;
		AIT_ASSERT(0,  ss.str());
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) 
	{
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::stringstream ss;
		ss<<"Error linking shader program: "<<errorLog<<std::endl;
		AIT_ASSERT(0,  ss.str());
    }

    glUseProgram(shaderProgram);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Attribute Interpolation");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		std::stringstream ss;
		ss<<"Error: "<<glewGetErrorString(res)<<"\n";
		AIT_ASSERT(0,  ss.str());
    }

	buildShaders();

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 

	// Create a vertex buffer
	createVertexBuffer();

    glutMainLoop();
    
    return 0;
}