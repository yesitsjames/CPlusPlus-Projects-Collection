#include "renderable.h"
#include "shadertechnique.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const int windowWidth = 1024;
const int windowHeight = 768;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texture Mapping");

    initializeGlutCallbacks();

    // Initialize GLEW
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        std::cerr << "Error: " << glewGetErrorString(res) << "\n";
        return 1;
    }

    buildShaders();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable backface culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialize components
    initLights();
    initTexture("texture.bmp");
    createVertexBuffer();

    glutMainLoop();

    return 0;
}