#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

GLuint VBO1;
GLuint VBO2;
GLuint VBO3;
GLuint VBO4;
GLuint VBO5;
GLuint VBO6;

const int NUMVERTS = 600;

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_POINTS, 0, 9);


    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_LINES, 10, 19);


    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_LINES, 20, 29);


    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_TRIANGLES, 30, 47);


    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_TRIANGLES, 48, 59);

    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(00);
    glDrawArrays(GL_TRIANGLES, 60, 68);


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
    // Create some vertices to put in our VBO.

    //V0 - Point List
    class PointList {
    public:
        vec3 vertices5[NUMVERTS] = {
    vec3(0.95f, 0.95f, 0.0f),
    vec3(0.90f, 0.95f, 0.0f),
    vec3(0.85f, 0.95f, 0.0f),
    vec3(0.95f, 0.90f, 0.0f),
    vec3(.90f, 0.90f, 0.0f),
    vec3(0.85f, 0.90f, 0.0f),
    vec3(0.95f, 0.85f, 0.0f),
    vec3(0.90f, 0.85f, 0.0f),
    vec3(0.85f, 0.85f, 0.0f),
    vec3(0.95f, 0.80f, 0.0f),
        };


        //V1 - Line List
        class LineList {
        public:
            vec3 vertices5[NUMVERTS] = {

        vec3(0.75f, 0.75f, 0.0f),
        vec3(0.95f, 0.75f, 0.0f),
        vec3(0.75f, 0.7f, 0.0f),
        vec3(0.95f, 0.7f, 0.0f),
        vec3(0.75f, 0.65f, 0.0f),
        vec3(0.95f, 0.65f, 0.0f),
        vec3(0.75f, 0.6f, 0.0f),
        vec3(0.95f, 0.6f, 0.0f),
        vec3(0.75f, 0.55f, 0.0f),
        vec3(0.95f, 0.55f, 0.0f),
            };

            //V2 - Line Strip
            class LineStrip {
            public:
                vec3 vertices5[NUMVERTS] = {

            vec3(-0.95f, 0.0f, 0.0f),
            vec3(-0.4f, -0.05f, 0.0f),

            vec3(-0.4f, -0.05f, 0.0f),
            vec3(-0.95f, -0.1f, 0.0f),

            vec3(-0.95f, -0.1f, 0.0f),
            vec3(-0.4f, -0.15f, 0.0f),

            vec3(-0.4f, -0.15f, 0.0f),
            vec3(-0.95f, -.3f, 0.0f),

            vec3(-0.95f, -0.3f, 0.0f),
            vec3(-0.4f, -0.45f, 0.0f),
                };

                //V3 - Triangle List
                class TriangleList {
                public:
                    vec3 vertices5[NUMVERTS] = {

                    vec3(0.0f, 0.95f, 0.0f),
                    vec3(-0.2f, 0.9f, 0.0f),
                    vec3(0.0f, 0.85f, 0.0f),

                        vec3(0.0f, 0.95f, 0.0f),
                        vec3(0.2f, 0.9f, 0.0f),
                        vec3(0.0f, 0.85f, 0.0f),


                    vec3(0.0f, 0.85f, 0.0f),
                    vec3(-0.2f, 0.9f, 0.0f),
                    vec3(-0.2f, 0.7f, 0.0f),

                    vec3(-0.2f, 0.7f, 0.0f),
                    vec3(0.0f, 0.85f, 0.0f),
                    vec3(0.0f, 0.65f, 0.0f),

                    vec3(0.0f, 0.85f, 0.0f),
                    vec3(0.2f, 0.9f, 0.0f),
                    vec3(0.2f, 0.7f, 0.0f),

                    vec3(0.2f, 0.7f, 0.0f),
                    vec3(0.0f, 0.85f, 0.0f),
                    vec3(0.0f, 0.65f, 0.0f),

                    };

                    //V4 - Triangle Strip
                    class TriangleStrip {
                    public:
                        vec3 vertices5[NUMVERTS] = {


            vec3(-0.6f, -0.6f, 0.0f),
            vec3(-0.8f, -0.8f, 0.0f),
            vec3(-0.4f, -0.8f, 0.0f),

            vec3(-0.3f, -0.6f, 0.0f),
            vec3(-0.5f, -0.8f, 0.0f),
            vec3(-0.1f, -0.8f, 0.0f),

            vec3(0.f, -0.6f, 0.0f),
            vec3(-0.2f, -0.8f, 0.0),
            vec3(0.2f, -0.8f, 0.0f),

            vec3(0.3f, -0.6f, 0.0f),
            vec3(0.5f, -0.8f, 0.0f),
            vec3(0.1f, -0.8f, 0.0f),
                        };


                        //V5 - Face (Triple Triangle = Amused Face)
                        class Face {
                        public:
                            vec3 vertices5[NUMVERTS] = {
                                //eye 1
                                vec3(-0.95f, .95f, 0.0f),
                                vec3(-0.8f, .90f, 0.0f),
                                vec3(-0.75f, .95f, 0.0f),

                                //eye 2
                                vec3(-0.65f, .95f, 0.0f),
                                vec3(-0.55f, .90f, 0.0f),
                                vec3(-0.45f, .95f, 0.0f),

                                //mouth
                                vec3(-0.75f, .80f, 0.0f),
                                vec3(-0.7f, .7f, 0.0f),
                                vec3(-0.65f, .8f, 0.0f),
                            };


                            //VBOs


                            int main(int argc, char** argv)
                            {
                                glutInit(&argc, argv);
                                glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
                                glutInitWindowSize(1024, 768);
                                glutInitWindowPosition(100, 100);
                                glutCreateWindow("First Triangle");

                                initializeGlutCallbacks();

                                // Must be done after glut is initialized!
                                GLenum res = glewInit();
                                if (res != GLEW_OK)
                                {
                                    cerr << "Error: " << glewGetErrorString(res) << "\n";
                                    return 1;
                                }

                                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

                                // Create a vertex buffer
                                //createVertexBuffer();

                                glutMainLoop();

                                return 0;
                            }

                            //Q3
                            // The max range is 1 and -1
                        };
                    };
                };
            };
        };
    };