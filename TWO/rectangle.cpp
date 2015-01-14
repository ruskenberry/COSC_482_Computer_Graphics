#include "rectangle.h"
#define PI 3.1415926535897932385

rectangle::rectangle() {
    load();
}

rectangle::rectangle(GLfloat w, GLfloat h) {
    width = w;
    height = h;
    load();
}

rectangle::rectangle(GLfloat w, GLfloat h, GLfloat r, GLfloat g, GLfloat b) {
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
    load();
}

rectangle::~rectangle() {}

void rectangle::setWidth(GLfloat w) {
    width = w;
    reloadData();
}

void rectangle::setHeight(GLfloat h) {
    height = h;
    reloadData();
}

void rectangle::setColor(GLfloat r, GLfloat g, GLfloat b) {
    red = r;
    green = g;
    blue = b;
    reloadData();
}

void rectangle::setAll(GLfloat w, GLfloat h, GLfloat r, GLfloat g, GLfloat b) {
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
    reloadData();
}

void rectangle::setPipelinePositions(GLint v, GLint c) {
    vPosition = v;
    vColor = c;
}

void rectangle::setRotation(GLfloat r) {
    rotation = r;
}

void rectangle::setScale(GLfloat s) {
    scale = s;
}

void rectangle::setTranslate(GLfloat x, GLfloat y) {
    translateX = x;
    translateY = y;
}

void rectangle::setRotationSpeed(GLfloat r) {
    rotationSpeed = r;
}

void rectangle::setScaleSpeed(GLfloat s) {
    scaleSpeed = s;
}

void rectangle::setTranslateSpeed(GLfloat x, GLfloat y) {
    translateXSpeed = x;
    translateYSpeed = y;
}

GLfloat rectangle::getWidth() {
    return width;
}

GLfloat rectangle::getHeight() {
    return height;
}

GLfloat rectangle::getRotation() {
    return rotation;
}

GLfloat rectangle::getScale() {
    return scale;
}

GLfloat rectangle::getTranslateX() {
    return translateX;
}

GLfloat rectangle::getTranslateY() {
    return translateY;
}

GLfloat rectangle::getRotationSpeed() {
    return rotationSpeed;
}

GLfloat rectangle::getScaleSpeed() {
    return scaleSpeed;
}

GLfloat rectangle::getTranslateSpeedX() {
    return translateXSpeed;
}

GLfloat rectangle::getTranslateSpeedY() {
    return translateYSpeed;
}

void rectangle::updateTransformations() {
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

mat4 rectangle::getTransformationMatrix() {
    return (Translate(translateX, translateY, 0) * Scale(scale) * RotateZ(rotation));
}

void rectangle::load() {
    GLfloat vertices[] {
        -(width/2), (height/2), 0, 1,
        -(width/2), -(height/2), 0, 1,
        (width/2), (height/2), 0, 1,
        (width/2), -(height/2), 0, 1
    };

    GLfloat colors[] {
        red, green, blue,
        red, green, blue,
        red, green, blue,
        red, green, blue
    };

    GLushort vertex_indices[] {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &vboptr);
    glBindVertexArray(vboptr);

    GLuint eboptr;
    glGenBuffers(1, &eboptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboptr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    glGenBuffers(1, &bufptr);
    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeof(vertices)));
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

void rectangle::reloadData() {
    GLfloat vertices[] {
        -(width/2), (height/2), 0, 1,
        -(width/2), -(height/2), 0, 1,
        (width/2), (height/2), 0, 1,
        (width/2), -(height/2), 0, 1
    };

    GLfloat colors[] {
        red, green, blue,
        red, green, blue,
        red, green, blue,
        red, green, blue
    };

    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
}

void rectangle::draw() {
    glBindVertexArray(vboptr);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}
