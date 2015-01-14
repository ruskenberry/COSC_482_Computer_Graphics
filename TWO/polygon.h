#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include "vec_mat.h"

#define BUFFER_OFFSET(x) ((const void*) (x))

class polygon
{
public:
    polygon();
    polygon(GLfloat n);
    polygon(GLfloat n, GLfloat rad);
    polygon(GLfloat n, GLfloat rad, GLfloat r, GLfloat g, GLfloat b);
    ~polygon();

    void setSides(GLint n);
    void setRadius(GLfloat rad);
    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setAll(GLint n, GLfloat rad, GLfloat r, GLfloat g, GLfloat b);
    void setPipelinePositions(GLint v, GLint c);

    void setRotation(GLfloat r);
    void setScale(GLfloat s);
    void setTranslate(GLfloat x, GLfloat y);

    void setRotationSpeed(GLfloat r);
    void setScaleSpeed(GLfloat s);
    void setTranslateSpeed(GLfloat x, GLfloat Y);

    GLint getSides();
    GLfloat getRadius();

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
    GLint sides = 4;
    GLfloat radius = 1;
    GLfloat red = 1;
    GLfloat green = 1;
    GLfloat blue = 1;

    GLfloat rotation = 0;
    GLfloat scale = 1;
    GLfloat translateX = 0;
    GLfloat translateY = 0;

    GLfloat rotationSpeed = 0;
    GLfloat scaleSpeed = 1;
    GLfloat translateXSpeed = 0;
    GLfloat translateYSpeed = 0;

    GLuint vboptr;
    GLuint iptr;
    GLuint eboptr;
    GLuint bufptr;

    GLfloat *points = NULL;
    GLuint *indices = NULL;
    GLfloat *colors = NULL;

    GLint vPosition = 0;
    GLint vColor = 1;
};

#endif // POLYGON_H_INCLUDED
