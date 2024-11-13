//
//-------------------- for the practice4_Graph ----------------------
//

#include<game_object.h>
#include"../4.1_undirectedGraph/game.h"
#include<iostream>

#define PI 3.14159265358979323846

const int pointNum = 30;

painter::Node::Node(GLfloat x, GLfloat y, Shader* shader, GLenum shp, GLfloat radius)
    : radius(radius), shader(shader) {

    vertices = getArc(x, y, radius);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*stride*2, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //std::cout << glGetError() << std::endl;
}

GLfloat* painter::Node::getArc(GLfloat x, GLfloat y, GLfloat radius) {
    stride = (pointNum + 2);
    GLfloat* vertices = new GLfloat[stride*2];

    vertices[0] = x;
    vertices[1] = y;

    float scale = WindowParas::getInstance().defaultAlpha;

    for (int i = 0; i <= pointNum; i++) {
        float angle = 2.0f * PI * i / pointNum;
        vertices[i * 2 + 2] = x + radius * cos(angle) / scale;
        vertices[i * 2 + 3] = y + radius * sin(angle);
    }

    //std::cout << sizeof(vertices) << std::endl;
    return vertices;
}

void painter::Node::draw() const {
    shader->use();
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_FAN, 0, stride);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
    //std::cout << glGetError() << std::endl;
}
