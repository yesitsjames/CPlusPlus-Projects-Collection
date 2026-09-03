#include "Renderable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

// Constructor
Renderable::Renderable() : vbo(0), textureId(0), numVerts(0) {
    position = vec3(0.0f, 0.0f, 0.0f);
    rotation = vec3(0.0f, 0.0f, 0.0f);
    scale = vec3(1.0f, 1.0f, 1.0f);
}

// Create VBO from array of vertices
void Renderable::createVBO(SimpleVertex vertices[], int nv) {
    numVerts = nv;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * numVerts, vertices, GL_STATIC_DRAW);
}

// Load vertices from OBJ file
bool Renderable::loadFromOBJ(const string& filename) {
    ifstream myReadFile;
    myReadFile.open(filename);

    if (!myReadFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    int numVertices = 0;
    int numFaces = 0;
    int numTexCoords = 0;
    string myText;

    // count the number of vertices, faces, and texture coordinates
    while (getline(myReadFile, myText)) {
        istringstream linestream(myText);
        string prefix;
        linestream >> prefix;

        //looks through our files for the "v" vertex position "f" for face definition and "vt" for texture cords

        if (prefix == "v") {
            numVertices++;
        }
        else if (prefix == "f") {
            numFaces++;
        }
        else if (prefix == "vt") {
            numTexCoords++;
        }
    }

    cout << "Vertices: " << numVertices << ", Faces: " << numFaces << endl;

    // Allocate arrays (for triangles)
    vec3* tempVerts = new vec3[numVertices];
    vec2* texCoords = new vec2[numTexCoords];
    SimpleVertex* vertices = new SimpleVertex[numFaces * 3]; // 3 vertices per face (triangles)

    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);

    int vertIndex = 0;
    int texIndex = 0;
    int faceIndex = 0;

    //reads the data
    while (getline(myReadFile, myText)) {
        istringstream linestream(myText);
        string prefix;
        linestream >> prefix;
                                        //all parsing
                //finds the "v's, vt's, f's" from the obj files 
        if (prefix == "v") {
            float x, y, z;
            linestream >> x >> y >> z;
            tempVerts[vertIndex++] = vec3(x, y, z);
        }
        else if (prefix == "vt") {
            float u, v;
            linestream >> u >> v;
        }
        else if (prefix == "f") {
            for (int i = 0; i < 3; i++) { 
                string vert;
                linestream >> vert;



                //parse position index
                size_t pos = vert.find('/'); //use bunny.obj as an example, goes through the face definitions
                int v_idx = stoi(vert.substr(0, pos)) - 1; 
                //since obj starts at 1 and c++ starts at 0, you need  to start at 0 hence why we need the -1
                //needs the -1 because of the array
                int t_idx = -1;
                if (pos + 1 < vert.length()) {
                    string texPart = vert.substr(pos + 1);
                    size_t nextPos = texPart.find('/');
                    if (nextPos != string::npos) {
                        texPart = texPart.substr(0, nextPos);
                    }
                    if (!texPart.empty()) {
                        t_idx = stoi(texPart) - 1;
                    }
                }

                vertices[faceIndex].pos = tempVerts[v_idx];

                
                vertices[faceIndex].normal = vec3(0.0f, 0.0f, 1.0f);

                // just if i needed to set texture coords (experimented with but couldnt get completely working for all the textures)
                if (t_idx >= 0 && t_idx < numTexCoords) {
                    vertices[faceIndex].texcoord = texCoords[t_idx];
                }
                else {
                    vertices[faceIndex].texcoord = vec2(0.0f, 0.0f);
                }

                faceIndex++;
            }
        }
    }

   // myReadFile.close();

    // Upload to GPU
    numVerts = numFaces * 3; //3 vertices im gonna render
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * numVerts, vertices, GL_STATIC_DRAW);

    //cleaning up (not sure if needed in the end but added anyway)

    return true;
}

// Set position
void Renderable::setPosition(const vec3& pos) {
    position = pos;
}

// Set rotation
void Renderable::setRotation(const vec3& rot) {
    rotation = rot;
}

// Set scale
void Renderable::setScale(const vec3& s) {
    scale = s;
}

// Set texture
void Renderable::setTexture(const char* imagePath) {
    
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    unsigned char* data;


    //debugged and ended up with this file opener (non traditional but it works)
    FILE* file = fopen(imagePath, "rb");
    if (!file) {
        std::cerr << imagePath << " could not be opened." << std::endl;
        return;
    }

    // reads the header
    if (fread(header, 1, 54, file) != 54) {
        std::cerr << "Not a correct BMP file" << std::endl;
        fclose(file);
        return;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        std::cerr << "Not a correct BMP file" << std::endl;
        fclose(file);
        return;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3; 
    if (dataPos == 0) dataPos = 54; 

    data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    fclose(file);

    glGenTextures(1, &textureId);

    
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    delete[] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    std::cout << "Loaded texture: " << imagePath << " (" << width << "x" << height << ")" << std::endl;
}

mat4 Renderable::getModelToWorldMatrix() {
    mat4 transform = mat4(1.0f);

    transform = translate(transform, position);

    transform = rotate(transform, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    transform = rotate(transform, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    transform = rotate(transform, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, scale);

    return transform;
}

void Renderable::display(GLuint programID, const Camera& camera) {
    mat4 modelToWorldTransform = getModelToWorldMatrix();
    GLuint modelToWorldLoc = glGetUniformLocation(programID, "gModelToWorldTransform");
    glUniformMatrix4fv(modelToWorldLoc, 1, GL_FALSE, &modelToWorldTransform[0][0]);

    mat4 worldToViewToProjectionTransform = camera.getViewProjectionMatrix();
    GLuint worldToViewProjLoc = glGetUniformLocation(programID, "gWorldToViewToProjectionTransform");
    glUniformMatrix4fv(worldToViewProjLoc, 1, GL_FALSE, &worldToViewToProjectionTransform[0][0]);

    if (textureId != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        GLuint texSamplerLoc = glGetUniformLocation(programID, "gTextureSampler");
        glUniform1i(texSamplerLoc, 0);
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);  
    glEnableVertexAttribArray(2);  

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)24);

    glDrawArrays(GL_TRIANGLES, 0, numVerts);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}