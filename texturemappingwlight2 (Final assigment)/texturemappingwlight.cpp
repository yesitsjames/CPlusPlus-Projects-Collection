#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <string>
#include <vector> 

#include "Renderable.h"
#include "ShaderTechnique.h"
#include "Camera.h"
#include "SimpleVertex.h"

using namespace std;
using namespace glm;

const int windowWidth = 1024;
const int windowHeight = 768;

ShaderTechnique shader;
std::vector<Renderable*> renderables; 
Camera camera;

bool keys[256] = { false };
float cameraSpeed = 0.05f;
float rotationSpeed = 0.05f;
std::vector<vec3> initialRotations;

static void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
}

static void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

static void handleInput() {
    if (keys['i'] || keys['I']) { //zoom in
        camera.moveForward(cameraSpeed);
   }
    if (keys['k'] || keys['K']) { //zoom out
        camera.moveForward(-cameraSpeed);
    }
    if (keys['j'] || keys['J']) { //just a slightly faster way of going left
        camera.moveRight(-cameraSpeed);
    }
    if (keys['l'] || keys['L']) { //just a slightly faster way of going right
        camera.moveRight(cameraSpeed);
    }
    if (keys['q'] || keys['Q']) { //move up
        camera.moveUp(cameraSpeed);
    }
    if (keys['e'] || keys['E']) { //move down
        camera.moveUp(-cameraSpeed);
    }
    
    //standard movement
    if (keys['w'] || keys['W']) { //up
        camera.rotatePitch(glm::radians(rotationSpeed));
    }
    if (keys['s'] || keys['S']) { //down
        camera.rotatePitch(glm::radians(-rotationSpeed));
    }
    if (keys['a'] || keys['A']) { //left
        camera.rotateYaw(glm::radians(rotationSpeed));
    }
    if (keys['d'] || keys['D']) {//right
        camera.rotateYaw(glm::radians(-rotationSpeed));
    }
}

//light set up, directional movement, the light will move position to show the different obj's
static void renderSceneCallBack() {
    handleInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint programID = shader.getShaderProgram();
    glUseProgram(programID);

    vec3 ambientLightIntensity = vec3(0.1f, 0.1f, 0.1f);
    GLuint ambientLoc = glGetUniformLocation(programID, "gAmbientLightIntensity");
    glUniform3fv(ambientLoc, 1, &ambientLightIntensity[0]);

    vec3 directionalLightDirection = vec3(0.0f, 0.0f, -1.0f);
    directionalLightDirection = normalize(directionalLightDirection);
    GLuint dirLightDirLoc = glGetUniformLocation(programID, "gDirectionalLightDirection");
    glUniform3fv(dirLightDirLoc, 1, &directionalLightDirection[0]);

    vec3 directionalLightIntensity = vec3(0.8f, 0.8f, 0.8f);
    GLuint dirLightIntensityLoc = glGetUniformLocation(programID, "gDirectionalLightIntensity");
    glUniform3fv(dirLightIntensityLoc, 1, &directionalLightIntensity[0]);

    GLuint kaLoc = glGetUniformLocation(programID, "gKa");
    glUniform1f(kaLoc, 0.2f);

    GLuint kdLoc = glGetUniformLocation(programID, "gKd");
    glUniform1f(kdLoc, 0.8f);

    static float angle = 0.0f;
    angle += 0.5f;


    //so to make the effect of the light changing
    //i just made it so when a surface normal points more directly toward the lights direction
    //the surface would get more light (so like when the objects go brighter and darker in turns)
    for (size_t i = 0; i < renderables.size(); i++) {
        vec3 baseRotation = initialRotations[i];

        vec3 rotationUpdate;

        switch (i % 5) {
        case 0: 
            rotationUpdate = vec3(baseRotation.x, baseRotation.y + angle, baseRotation.z);
            break;
        case 1: 
            rotationUpdate = vec3(baseRotation.x + angle, baseRotation.y, baseRotation.z);
            break;
        case 2: 
            rotationUpdate = vec3(baseRotation.x, baseRotation.y, baseRotation.z + angle);
            break;
        case 3: 
            rotationUpdate = vec3(baseRotation.x + angle * 0.3f, baseRotation.y + angle, baseRotation.z);
            break;
        case 4:
            rotationUpdate = vec3(baseRotation.x + angle * 0.5f, baseRotation.y + angle, baseRotation.z + angle * 0.7f);
            break;
        }

        renderables[i]->setRotation(rotationUpdate);
    }

    for (Renderable* renderable : renderables) {
        renderable->display(programID, camera);
    }

    glutSwapBuffers();
}

static void createCube(const string& texturePath, const vec3& position, const vec3& rotation = vec3(0.0f), const vec3& scale = vec3(1.0f)) {
    // Define cube vertices
    SimpleVertex vertices[] = {
        // Front face
        {vec3(-0.2f, 0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f, 0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
        {vec3(0.2f,-0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f, 0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f,-0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f,-0.2f, 0.2f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},

        // Right face
        {vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f, 0.2f,-0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
        {vec3(0.2f,-0.2f,-0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f,-0.2f,-0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(0.2f,-0.2f, 0.2f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},

        // Back face
        {vec3(0.2f, 0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(0.0f, 1.0f)},
        {vec3(-0.2f, 0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(1.0f, 1.0f)},
        {vec3(-0.2f,-0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(1.0f, 0.0f)},
        {vec3(0.2f, 0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(0.0f, 1.0f)},
        {vec3(-0.2f,-0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(1.0f, 0.0f)},
        {vec3(0.2f,-0.2f,-0.2f), vec3(0.0f, 0.0f,-1.0f), vec2(0.0f, 0.0f)},

        // Left face
        {vec3(-0.2f, 0.2f,-0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(-0.2f, 0.2f, 0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
        {vec3(-0.2f,-0.2f, 0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f, 0.2f,-0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(-0.2f,-0.2f, 0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f,-0.2f,-0.2f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},

        // Top face
        {vec3(-0.2f, 0.2f,-0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f, 0.2f,-0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
        {vec3(0.2f, 0.2f, 0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f, 0.2f,-0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f, 0.2f, 0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f, 0.2f, 0.2f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},

        // Bottom 
        {vec3(-0.2f,-0.2f,-0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(-0.2f,-0.2f, 0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(0.0f, 0.0f)},
        {vec3(0.2f,-0.2f, 0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(-0.2f,-0.2f,-0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(0.0f, 1.0f)},
        {vec3(0.2f,-0.2f, 0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(1.0f, 0.0f)},
        {vec3(0.2f,-0.2f,-0.2f), vec3(0.0f,-1.0f, 0.0f), vec2(1.0f, 1.0f)}
    };

    Renderable* cube = new Renderable();
    cube->createVBO(vertices, 36);  
    cube->setTexture(texturePath.c_str());
    cube->setPosition(position);
    cube->setRotation(rotation);
    cube->setScale(scale);

    renderables.push_back(cube);
    initialRotations.push_back(rotation); 
}

static void loadModel(const string& objPath, const string& texturePath, const vec3& position, const vec3& rotation = vec3(0.0f), const vec3& scale = vec3(1.0f)) {
    Renderable* model = new Renderable();

    cout << "Loading OBJ model: " << objPath << endl;

    if (model->loadFromOBJ(objPath)) {
        model->setTexture(texturePath.c_str());
        model->setPosition(position);
        model->setRotation(rotation);
        model->setScale(scale);
        renderables.push_back(model);
        initialRotations.push_back(rotation); 
        cout << "Model loaded successfully" << endl;
    }
    else {
        cout << "Failed to load model: " << objPath << endl;
        delete model;
    }
}

static void initializeGlutCallbacks() {
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
}

static void initializeScene() {
    // Initialize camera
    camera = Camera(
        vec3(0.0f, 0.0f, 5.0f),  // Position 
        vec3(0.0f, 0.0f, 0.0f),   // Target
        vec3(0.0f, 1.0f, 0.0f),   // Up
        45.0f,                     // Field of view
        (float)windowWidth / (float)windowHeight, // Aspect ratio
        0.1f,                      // Near clip
        100.0f                     // Far clip
    );

    createCube("555.bmp", vec3(0.0f, 0.0f, 0.0f));

    // Load all 5 OBJ models
    loadModel("box.txt", "555.bmp", vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 45.0f, 0.0f), vec3(0.2f, 0.2f, 0.2f));
    loadModel("bunny.txt", "333.bmp", vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
    loadModel("monkey.txt", "555.bmp", vec3(0.0f, 1.0f, 0.0f), vec3(45.0f, 45.0f, 0.0f), vec3(0.25f, 0.25f, 0.25f));
    loadModel("sphere.txt", "555.bmp", vec3(0.0f, -1.0f, 0.0f), vec3(90.0f, 0.0f, 0.0f), vec3(0.2f, 0.2f, 0.2f));
    loadModel("triangle.txt", "555.bmp", vec3(2.0f, 0.0f, -1.0f), vec3(0.0f, -90.0f, 0.0f), vec3(0.05f, 0.05f, 0.05f));
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL 3D Scene with Rotating OBJ Models");

    initializeGlutCallbacks();

    // Initialize GLEW
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        cerr << "Error: " << glewGetErrorString(res) << endl;
        return 1;
    }

    //how I loaded it for previous projects
    shader.loadShaders("vertexShader.glsl", "fragmentShader.glsl");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    initializeScene();

    cout << "I/K: Move forward/backward" << endl;
    cout << "J/L: Strafe left/right" << endl;
    cout << "Q/E: Move up/down" << endl;
    cout << "W/S: Look up/down" << endl;
    cout << "A/D: Look left/right" << endl;

    glutMainLoop();

    return 0;
}