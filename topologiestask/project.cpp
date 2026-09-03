#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Renderable.h"


using namespace std;
using namespace glm;

GLuint VBO;
const int NUMVERTS = 3;
const int NUMVERTS2 = 3;

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);
    glDrawArrays(GL_TRIANGLES, 0, NUMVERTS2);

    rd = 

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

//static void createVertexBuffer()
//{
//}

static void createRenderables()
{
    const int NUMVERTS = 3;
    vec3 vertices[NUMVERTS];
    vertices[0] = vec3(-0.5f, -0.5f, 0.0f);
    vertices[1] = vec3(0.5f, -0.5f, 0.0f);
    vertices[2] = vec3(0.0f, 0.0f, 0.0f);
    rd[0].createVbo(vertices, NUMVERTS);

    const int NUMVERTS = 3;
    vec3 vertices[NUMVERTS2];
    vertices[0] = vec3(-0.0f, -1.0f, 0.0f);
    vertices[1] = vec3(1.0f, -0.5f, 0.0f);
    vertices[2] = vec3(0.0f, 1.0f, 0.0f);
    rd[1].createVbo(vertices, NUMVERTS);


}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

int main(int argc, char** argv)
{

}