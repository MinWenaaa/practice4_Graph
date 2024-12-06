//
//-------------------- for the practice4_Graph ----------------------
//

#include<game_object.h>
#include<algorithm>
#include<cmath>
#include"../4.1_undirectedGraph/game.h"
#include<iostream>

painter::Node::Node(GLfloat x, GLfloat y, GLuint color, Shader* shader, GLenum shp, GLfloat pocess)
    : pocess(pocess), shader(shader), isInited(false), color(color), x(x), y(y) {

    GLuint colors[stride_node];
    for (int i = 0; i < stride_node; i++) {
        colors[i] = color;
    }
    std::cout << "Node Init:" << glGetError() << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO_cover);
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    glGenBuffers(1, &coverVBO_c);
    glGenBuffers(1, &coverVBO_p);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_node, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "Node Init End: " << glGetError() << std::endl;
}

void painter::Node::setCoverColor(GLuint c) {
    newColor = c;
    GLuint colors[stride_node];
    for (int i = 0; i < stride_node; i++) {
        colors[i] = c;
    }
    glBindVertexArray(VAO_cover);
    glBindBuffer(GL_ARRAY_BUFFER, coverVBO_c);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_node, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void painter::Node::draw_baseLayer() {
    //std::cout << "Node Draw Begin: " << glGetError() << std::endl;
    if (!isInited) {
        pocess += 0.0002;
        float positions[stride_node * 2];
        getArc(positions, pocess);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_node * 2, positions, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        if (pocess > 0.03) isInited = true;
    }
    shader->use();
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, circle_pointNum+2);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void painter::Node::draw_coverLayer(float &p) {
    p += 0.02;
    float positions[stride_node * 2];
    getArc(positions, p*0.03);
    glBindVertexArray(VAO_cover);
    glBindBuffer(GL_ARRAY_BUFFER, coverVBO_p);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_node * 2, positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    shader->use();
    glBindVertexArray(VAO_cover);
    glDrawArrays(GL_TRIANGLE_FAN, 0, circle_pointNum + 2);
    glBindVertexArray(0);

    if (p > 1) setColor();
}

void painter::Node::getArc(GLfloat* data, float p) {
    data[0] = x;
    data[1] = y;

    float scale = WindowParas::getInstance().defaultAlpha;
    float angle = 0;
    for (int i = 0; i <= circle_pointNum; i++) {
        angle = 2.0f * PI * i / circle_pointNum;
        data[i * 2 + 2 ] = x + p * cos(angle) / scale;
        data[i * 2 + 3] = y + p * sin(angle);
        //std::cout << data[i * 2] << ", " << data[i * 2 + 1] << std::endl;
    }

    //std::cout << std::endl;
}

void painter::Node::setColor() {
    color = newColor;
    GLuint colors[stride_node];
    for (int i = 0; i < stride_node; i++) {
        colors[i] = color;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_node, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

painter::Edge::Edge(GLfloat* positions, GLint color, int v1, int v2, int start, Shader* shader)
    : shader(shader), start(start), isInited(false), color(color), v1(v1), v2(v2), poccess(0) {

    std::copy(positions, positions + 4, node);
    delta = 0.0002 / sqrt(pow(node[0] - node[2], 2) + pow(node[1] - node[3], 2));
    GLuint colors[stride_line];
    for (int i = 0; i < stride_line; i++) {
        colors[i] = color;
    }
    std::cout << "Edge Init:" << glGetError() << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO_cover);
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    glGenBuffers(1, &coverVBO_c);
    glGenBuffers(1, &coverVBO_p);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_line, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "Edge Init End: " << glGetError() << std::endl;
}

void painter::Edge::setCoverColor(GLuint c) {
    newColor = c;
    GLuint colors[stride_line ];
    for (int i = 0; i < stride_line; i++) {
        colors[i] = c;
    }
    glBindVertexArray(VAO_cover);
    glBindBuffer(GL_ARRAY_BUFFER, coverVBO_c);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_line, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void painter::Edge::draw_baseLayer() {
    if (!isInited) {
        GLfloat position[8];
        poccess += delta;
        transform(position, poccess);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, position, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        if (poccess > 1) isInited = true;
    }
    shader->use();
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void painter::Edge::draw_coverLayer(float &p) {
    GLfloat position[8];
    p += delta;
    transform(position, p);
    glBindVertexArray(VAO_cover);
    glBindBuffer(GL_ARRAY_BUFFER, coverVBO_p);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, position, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (p > 1) setColor();

    shader->use();
    glBindVertexArray(VAO_cover);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void painter::Edge::transform(GLfloat* position, float p) {
    
    GLfloat sX, sY, eX, eY;
    if (start == v1) {
        sX = node[0]; sY = node[1]; eX = sX + p * (node[2] - sX); eY = sY + p * (node[3] - sY);
    } else {
        sX = node[2]; sY = node[3]; eX = sX + p * (node[0] - sX); eY = sY + p * (node[1] - sY);
    }
    
    float deltaX = eX - sX;
    float deltaY = eY - sY;
    float L = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    position[0] = sX + deltaY / L * 0.005;
    position[1] = sY - deltaX / L * 0.005;
    position[2] = sX - deltaY / L * 0.005;
    position[3] = sY + deltaX / L * 0.005;
    position[4] = eX + deltaY / L * 0.005;
    position[5] = eY - deltaX / L * 0.005;
    position[6] = eX - deltaY / L * 0.005;
    position[7] = eY + deltaX / L * 0.005;
}

void painter::Edge::setColor() {
    color = newColor;
    GLuint colors[stride_line];
    for (int i = 0; i < stride_line; i++) {
        colors[i] = color;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride_line, colors, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(GLuint), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}