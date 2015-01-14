#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "LoadShaders.h"
#include "vec_mat.h"
#include "rectangle.h"
#include "polygon.h"

long frames = 0;
int frameCount, currentTime, previousTime, fps, rNum, pNum;
GLuint projloc;
GLenum mode = GL_FILL;

double thisTime;
double ATime;
double seconds;

clock_t timer;
clock_t startTime;

rectangle *r;
polygon *p;

float randomNumber(float minValue, float maxValue)
{
    if (minValue == maxValue || minValue > maxValue)
        return maxValue;
    return (((((float) rand()) / (float) RAND_MAX) * (maxValue - minValue)) + minValue);
}

void init()
{
    rNum = (rand()%21)+5;
    r = new rectangle[rNum];
    for (int i = 0; i < rNum; i++) {
        r[i] = rectangle(1, 1, randomNumber(0,1), randomNumber(0,1), randomNumber(0,1));
        r[i].setTranslate(randomNumber(-7.5,7.5),randomNumber(-7.5,7.5));
        r[i].setRotation(randomNumber(0,360));
        r[i].setScale(randomNumber(0.8,1.2));
        r[i].setRotationSpeed(randomNumber(-2,2));
        r[i].setScaleSpeed(randomNumber(0.98,1));
        r[i].setTranslateSpeed(randomNumber(-0.2,0.2),randomNumber(-0.2,0.2));
    }
    pNum = (rand()%21)+5;
    p = new polygon[pNum];
    for (int i = 0; i < pNum; i++) {
        p[i] = polygon((rand()%8)+3, randomNumber(.25,.5), randomNumber(0,1), randomNumber(0,1), randomNumber(0,1));
        p[i].setTranslate(randomNumber(-7.5,7.5), randomNumber(-7.5,7.5));
        p[i].setRotation(randomNumber(0,360));
        p[i].setScale(randomNumber(0.8,1.2));
        p[i].setRotationSpeed(randomNumber(-2,2));
        p[i].setScaleSpeed(randomNumber(0.98,1));
        p[i].setTranslateSpeed(randomNumber(-0.2,0.2),randomNumber(-0.2,0.2));
    }

    ShaderInfo shaders[] {
        {GL_VERTEX_SHADER, "vertexShader.vert"},
        {GL_FRAGMENT_SHADER, "PassThrough.frag"},
        {GL_NONE, NULL}
    };
    program = LoadShaders(shaders);
    glUseProgram(program);

    projloc = glGetUniformLocation(program, "Model");
    startTime = clock();

    ATime = clock();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 033:  // ASCII Escape Key Code
            exit(EXIT_SUCCESS);
            break;
        case 'm': //Display Lines
            if (mode == GL_FILL)
                mode = GL_LINE;
            else
                mode = GL_FILL;
            glPolygonMode(GL_FRONT_AND_BACK, mode);
            break;
    }
    glutPostRedisplay();
}

//Print errors
void printOpenGLErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error: %s\n", errString);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < rNum; i++) {
        glUniformMatrix4fv(projloc, 1, GL_TRUE, r[i].getTransformationMatrix());
        r[i].draw();
    }
    for (int i = 0; i < pNum; i++) {
        glUniformMatrix4fv(projloc, 1, GL_TRUE, p[i].getTransformationMatrix());
        p[i].draw();
    }
    glutSwapBuffers();
    printOpenGLErrors();
}

//Keep Aspect ratio
void reshape(GLint width, GLint height)
{
    glViewport(0, 0, width, height);
    mat4 projection;
    if (height == 0 || width == 0)
        projection = Ortho2D(-1, 1, -1, 1);
    else if (width > height)
        projection = Ortho2D(-10.0*width/height, 10.0*width/height, -10, 10);
    else
        projection = Ortho2D(-10, 10, -10.0*height/width, 10.0*height/width);
    GLuint projloc = glGetUniformLocation(program, "Projection");
    glUniformMatrix4fv(projloc, 1, GL_TRUE, projection);
}

//cycle through rectangles and polygons to update transformation matrices
void update()
{
    for (int i = 0; i < rNum; i++)
        r[i].updateTransformations();
    for (int i = 0; i < pNum; i++)
        p[i].updateTransformations();
    glutPostRedisplay();
}

void timekeeper()
{
    // calculate fps
    timer = clock();
    double NowSec = (double)(timer - startTime)/CLOCKS_PER_SEC;
    frames++;
    if (frames % 10000 == 0)
        std::cout << "FPS: " << (int)(frames/NowSec) << std::endl;

    // call update every 120 times per second
    thisTime += ATime;
    if(thisTime >= 8.3) {
        thisTime = seconds;
        update();
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);

    if (glewInit()) {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit( EXIT_FAILURE );
    }
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(timekeeper);
    glutMainLoop();
}
