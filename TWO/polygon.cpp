#include "polygon.h"
#define PI 3.1415926535897932385

polygon::polygon() {
    load();
}

polygon::polygon(GLfloat n) {
    sides = n;
    load();
}

polygon::polygon(GLfloat n, GLfloat rad) {
    sides = n;
    radius = rad;
    load();
}

polygon::polygon(GLfloat n, GLfloat rad, GLfloat r, GLfloat g, GLfloat b) {
    sides = n;
    radius = rad;
    red = r;
    green = g;
    blue = b;
    load();
}

polygon::~polygon() {}

void polygon::setSides(GLint n) {
    sides = n;
    reloadData();
}

void polygon::setRadius(GLfloat rad) {
    radius = rad;
    reloadData();
}

void polygon::setColor(GLfloat r, GLfloat g, GLfloat b) {
    red = r;
    green = g;
    blue = b;
    reloadData();
}

void polygon::setAll(GLint n, GLfloat rad, GLfloat r, GLfloat g, GLfloat b) {
    sides = n;
    radius = rad;
    red = r;
    green = g;
    blue = b;
    reloadData();
}

void polygon::setPipelinePositions(GLint v, GLint c) {
    vPosition = v;
    vColor = c;
}

void polygon::setRotation(GLfloat r) {
    rotation = r;
}

void polygon::setScale(GLfloat s) {
    scale = s;
}

void polygon::setTranslate(GLfloat x, GLfloat y) {
    translateX = x;
    translateY = y;
}

void polygon::setRotationSpeed(GLfloat r) {
    rotationSpeed = r;
}

void polygon::setScaleSpeed(GLfloat s) {
    scaleSpeed = s;
}

void polygon::setTranslateSpeed(GLfloat x, GLfloat y) {
    translateXSpeed = x;
    translateYSpeed = y;
}

GLint polygon::getSides() {
    return sides;
}

GLfloat polygon::getRadius() {
    return radius;
}

GLfloat polygon::getRotation() {
    return rotation;
}

GLfloat polygon::getScale() {
    return scale;
}

GLfloat polygon::getTranslateX() {
    return translateX;
}

GLfloat polygon::getTranslateY() {
    return translateY;
}

GLfloat polygon::getRotationSpeed() {
    return rotationSpeed;
}

GLfloat polygon::getScaleSpeed() {
    return scaleSpeed;
}

GLfloat polygon::getTranslateSpeedX() {
    return translateXSpeed;
}

GLfloat polygon::getTranslateSpeedY() {
    return translateYSpeed;
}

void polygon::updateTransformations()
{

    rotation += rotationSpeed;

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int width = viewport[2];
    int height = viewport[3];
    float xscale = (float) width / (float) height;
    float yscale = 1;

    //"Breakout" bounce back
    translateX += translateXSpeed;
    if (translateX <= -10*xscale) {
        translateX = -10*xscale;
        translateXSpeed *= -1;
    } else if (translateX >= 10*xscale) {
        translateX = 10*xscale;
        translateXSpeed *= -1;
    }

    //"Breakout" bounce back
    translateY += translateYSpeed;
    if (translateY <= -10*yscale) {
        translateY = -10*yscale;
        translateYSpeed *= -1;
    } else if (translateY >= 10*yscale) {
        translateY = 10*yscale;
        translateYSpeed *= -1;
    }
    scale *= scaleSpeed;
    if (scale >= 2.5)
        scaleSpeed = 1 - (scaleSpeed - 1);
    else if (scale <= .2)
        scaleSpeed = 1 + (1 - scaleSpeed);
}

mat4 polygon::getTransformationMatrix() {
    return (Translate(translateX, translateY, 0) * Scale(scale) * RotateZ(rotation));
}

void polygon::load() {
    GLfloat pointz[sides*4];
    GLfloat colorz[sides*3];
    GLushort indicez[sides];

    for (int i = 0; i < sides*4; i+=4) {
        pointz[i+0] = radius * cos((i/4) * 2 * PI / sides);
        pointz[i+1] = radius * sin((i/4) * 2 * PI / sides);
        pointz[i+2] = 0;
        pointz[i+3] = 1;
    }

    for (int i = 0; i < sides*3; i+=3) {
        colorz[i+0] = red;
        colorz[i+1] = green;
        colorz[i+2] = blue;
    }

    for (int i = 0; i < sides; i++) {
        indicez[i] = i;
    }

    glGenVertexArrays(1, &vboptr);
    glBindVertexArray(vboptr);

    glGenBuffers(1, &eboptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicez), indicez, GL_STATIC_DRAW);

    glGenBuffers(1, &bufptr);
    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointz) + sizeof(colorz), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointz), pointz);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointz), sizeof(colorz), colorz);

    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeof(pointz)));
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

void polygon::reloadData() {
    GLfloat pointz[sides*4];
    GLfloat colorz[sides*3];
    GLushort indicez[sides];

    for (int i = 0; i < sides*4; i+=4) {
        pointz[i+0] = radius * cos((i/4) * 2 * PI / sides);
        pointz[i+1] = radius * sin((i/4) * 2 * PI / sides);
        pointz[i+2] = 0;
        pointz[i+3] = 1;
    }

    for (int i = 0; i < sides*3; i+=3) {
        colorz[i+0] = red;
        colorz[i+1] = green;
        colorz[i+2] = blue;
    }

    for (int i = 0; i < sides; i++) {
        indicez[i] = i;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicez), indicez, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointz) + sizeof(colorz), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointz), pointz);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointz), sizeof(colorz), colorz);
}

void polygon::draw() {
    glBindVertexArray(vboptr);
    glDrawElements(GL_TRIANGLE_FAN, sides, GL_UNSIGNED_SHORT, NULL);
}
