#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderable.h"
#include "camera.h"
#include "shadertechnique.h"
#include "simplevertex.h"
#include "uniformvariables.h"

using namespace std;
using namespace glm;

const int windowWidth = 1024;
const int windowHeight = 768;

// Global objects
Renderable* g_cube = nullptr;
Camera* g_camera = nullptr;
ShaderTechnique* g_shaderTechnique = nullptr;
float g_rotationAngle = 0.0f;

static void CreateCube() {
    SimpleVertex vertices[] = {
        // Side 1 Front
        {vec3(-1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
        {vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
        {vec3(1.0f, -1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
        {vec3(-1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
        {vec3(1.0f, -1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
        {vec3(-1.0f, -1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},

        // Side 2 Right Side
        {vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(1.0f, 1.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
        {vec3(1.0f, -1.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(1.0f, -1.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(1.0f, -1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},

        // Side 3 Back
        {vec3(1.0f, 1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
        {vec3(-1.0f, -1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
        {vec3(1.0f, 1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},
        {vec3(-1.0f, -1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
        {vec3(1.0f, -1.0f, -1.0f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},

        // Side 4 Left Side
        {vec3(-1.0f, 1.0f, -1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
        {vec3(-1.0f, -1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-1.0f, 1.0f, -1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(-1.0f, -1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)}
    };

    g_cube = new Renderable();
    if (!g_cube->Initialize(vertices, 24)) {
        cerr << "Cube initialization failed!" << endl;
        exit(1);
    }
}

static void RenderSceneCallback() {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update camera view and projection
    g_camera->Update();

    // Set combined view-projection matrix in shader
    UniformVariables::Get().SetWorldToViewToProjectionTransform(g_camera->GetViewProjectionMatrix());

    // Update model transform (rotation)
    g_rotationAngle += 1.0f;
    mat4 modelToWorldTransform = mat4(1.0f);
    modelToWorldTransform = rotate(modelToWorldTransform, radians(g_rotationAngle), vec3(0.0f, 1.0f, 0.0f));

    // Render cube
    g_cube->Render(modelToWorldTransform);

    // Swap buffers
    glutSwapBuffers();
}

static void InitializeGlutCallbacks() {
    glutDisplayFunc(RenderSceneCallback);
    glutIdleFunc(RenderSceneCallback);
}

static void InitializeGLContext() {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable backface culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

static void Cleanup() {
    if (g_cube) {
        delete g_cube;
        g_cube = nullptr;
    }
    if (g_camera) {
        delete g_camera;
        g_camera = nullptr;
    }
    if (g_shaderTechnique) {
        delete g_shaderTechnique;
        g_shaderTechnique = nullptr;
    }
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Cube with Texture");

    // Initialize GLEW
    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK) {
        cerr << "Error initializing GLEW: " << glewGetErrorString(glewInitResult) << endl;
        return 1;
    }

    // Initialize GL context and callbacks
    InitializeGLContext();
    InitializeGlutCallbacks();

    // Create shader technique
    g_shaderTechnique = new ShaderTechnique();
    if (!g_shaderTechnique->Initialize("vertexShader.glsl", "fragmentShader.glsl")) {
        cerr << "Shader initialization failed" << endl;
        Cleanup();
        return 1;
    }
    g_shaderTechnique->Use();


    UniformVariables::Get().InitializeLights();

    // Create camera
    g_camera = new Camera();
    g_camera->SetPerspectiveProjection(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

    // Create cube
    CreateCube();

    // Register cleanup function
    atexit(Cleanup);

    // Start main loop
    glutMainLoop();

    return 0;
}