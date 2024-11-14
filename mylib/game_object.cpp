//
//-------------------- for the practice4_Graph ----------------------
//

#include<game_object.h>
#include"../4.1_undirectedGraph/game.h"
#include<iostream>

#define PI 3.14159265358979323846

const int pointNum = 30;

painter::Node::Node(GLfloat x, GLfloat y, Shader* shader, GLenum shp, GLfloat radius)
    : radius(radius), shader(shader), moving(true), x(x), y(y) {

    stride = pointNum + 2;
    data  = new GLfloat[stride*2];
    getArc(x, y, radius, data);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*stride*2, data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //std::cout << glGetError() << std::endl;
}

void painter::Node::draw() {
    if (moving) {
        radius += 0.0005;
        getArc(x, y, radius, data);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride * 2, data, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    shader->use();
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_FAN, 0, stride);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
    //std::cout << glGetError() << std::endl;
    if (radius > 0.03) moving = false;
}

GLfloat* painter::Node::getArc(GLfloat x, GLfloat y, GLfloat radius, GLfloat*& data) {
    data[0] = x;
    data[1] = y;

    float scale = WindowParas::getInstance().defaultAlpha;
    for (int i = 0; i <= pointNum; i++) {
        float angle = 2.0f * PI * i / pointNum;
        data[i * 2 + 2] = x + radius * cos(angle) / scale;
        data[i * 2 + 3] = y + radius * sin(angle);
    }

    //std::cout << sizeof(vertices) << std::endl;
    return data;
}

painter::Edge::Edge(GLfloat* positions, int v1, int v2, Shader* shader, int stride) 
    : stride(stride), shader(shader), start(v1), moving(true), poccess(0) {
    vertices = new GLfloat[stride * 2];

    for (int i = 0; i < stride - 1; i++) {
        vertices[i * 2] = positions[1];
        vertices[i * 2 + 1] = positions[2];
    }
    vertices[stride * 2 - 2] = positions[4];
    vertices[stride * 2 - 1] = positions[5];
    
    bool walked[] = { true, true, false, false };
    node = new float[6];
    for (int i = 0; i < 6; i++) {
        node[i] = positions[i];
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride * 2, vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bool) * stride, walked, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 1, GL_BOOL, GL_FALSE, sizeof(bool), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void painter::Edge::draw() {
    if (moving) {
        transform();
    }
    shader->use();
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_LINES, 0, stride);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void painter::Edge::transform() {
    poccess += 0.005;
    
    GLfloat sX, sY, eX, eY;
    if (start == node[0]) {
        sX = node[1]; sY = node[2]; eX = node[4]; eY= node[5];
    } else {
        sX = node[4]; sY = node[5]; eX = node[1]; eY = node[2];
    }

    vertices[0] = sX;
    vertices[1] = sY;
    vertices[stride * 2 - 2] = eX;
    vertices[stride * 2 - 1] = eY;

    for (int i = 1; i < stride - 1; i++) {
        vertices[i * 2] = sX + poccess * (eX - sX);
        vertices[i * 2 + 1] = sY + poccess * (eY - sY);
    }

    if (poccess > 1) moving = false;
}