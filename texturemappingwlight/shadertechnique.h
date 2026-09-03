#include <string>

void buildShaders();
void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
const std::string readFileToString(const char* filename);