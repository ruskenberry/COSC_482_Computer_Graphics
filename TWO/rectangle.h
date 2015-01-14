#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vec_mat.h"

#define BUFFER_OFFSET(x) ((const void*) (x))

static GLuint program;

class rectangle
{
public:
    rectangle();
    rectangle(GLfloat w, GLfloat h);
    rectangle(GLfloat w, GLfloat h, GLfloat r, GLfloat g, GLfloat b);
    ~rectangle();

    void setWidth(GLfloat w);
    void setHeight(GLfloat h);
    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setAll(GLfloat w, GLfloat h, GLfloat r, GLfloat g, GLfloat b);

    void setPipelinePositions(GLint v, GLint c);
    void setRotation(GLfloat r);
    void setScale(GLfloat s);
    void setTranslate(GLfloat x, GLfloat y);

    void setRotationSpeed(GLfloat r);
    void setScaleSpeed(GLfloat s);
    void setTranslateSpeed(GLfloat x, GLfloat y);

    GLfloat getWidth();
    GLfloat getHeight();

    GLfloat getRotation();
    GLfloat getScale();
    GLfloat getTranslateX();
    GLfloat getTranslateY();

    GLfloat getRotationSpeed();
    GLfloat getScaleSpeed();
    GLfloat getTranslateSpeedX();
    GLfloat getTranslateSpeedY();

    void updateTransformations();
    mat4 getTransformationMatrix();

    void load();
    void reloadData();
    void draw();

private:
    GLfloat width = 1;
    GLfloat height = 1;
    GLfloat red = 1;
    GLfloat green = 0;
    GLfloat blue = 0;

    GLfloat rotation = 0;
    GLfloat scale = 1;
    GLfloat translateX = 0;
    GLfloat translateY = 0;

    GLfloat rotationSpeed = 0;
    GLfloat scaleSpeed = 1;
    GLfloat translateXSpeed = 0;
    GLfloat translateYSpeed = 0;

    GLuint vboptr;
    GLuint bufptr;
    GLuint iptr;

    GLint vPosition = 0;
    GLint vColor = 1;
};

#endif // RECTANGLE_H_INCLUDED
