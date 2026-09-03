#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "renderable.h"

using namespace std;
using namespace glm;

Renderable rd[2];

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 2; i++)
    {
        rd[i].render();
    }

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
}

static void createRenderables()
{
	// Create some vertices to put in our VBO.
    const int NUMVERTS = 3;
	vec3 vertices[NUMVERTS];
    vertices[0] = vec3(-0.5f, -0.5f, 0.0f);
    vertices[1] = vec3(0.5f, -0.5f, 0.0f);
    vertices[2] = vec3(0.0f, 0.0f, 0.0f);
    rd[0].createVbo(vertices, NUMVERTS);

    const int NUMVERTS2 = 3;
    vec3 vertices2[NUMVERTS2];
    vertices2[0] = vec3(-0.5f, 0.5f, 0.0f);
    vertices2[1] = vec3(0.5f, 0.5f, 0.0f);
    vertices2[2] = vec3(0.0f, 0.0f, 0.0f);
    rd[1].createVbo(vertices2, NUMVERTS2);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Project");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

	// Create a vertex buffer
    createRenderables();

    glutMainLoop();
    
    return 0;
}