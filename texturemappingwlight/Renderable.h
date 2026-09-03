#include <GL/glew.h>
#include <glm/glm.hpp>

extern GLuint VBO;
extern int NUMVERTS;

void createVertexBuffer();
void initLights();
void initTexture(const char* imagepath);
void renderSceneCallBack();
void initializeGlutCallbacks();
