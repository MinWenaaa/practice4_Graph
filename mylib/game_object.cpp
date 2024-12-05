//
//-------------------- for the practice4_Graph ----------------------
//

#include<game_object.h>
#include<algorithm>
#include<cmath>
#include"../4.1_undirectedGraph/game.h"
#include<iostream>

painter::Node::Node(GLfloat x, GLfloat y, GLint color, Shader* shader, GLenum shp, GLfloat pocess)
    : pocess(pocess), shader(shader), isDrawing(true), x(x), y(y) {

    const int stride = circle_pointNum + 2;
    float positions[stride*2];
    getArc(positions);
    int colors[stride]{ color };

    std::cout << "Node Init:" << glGetError() << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*stride*2, positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride * 2, colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, 1 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    std::cout << "Node Init End: " << glGetError() << std::endl;
}

void painter::Node::draw() {
    //std::cout << "Node Draw Begin: " << glGetError() << std::endl;
    if (isDrawing) {
        pocess += 0.0002;
        const int stride = circle_pointNum + 2;
        float positions[stride * 2];
        getArc(positions);
        glBindVertexArray(VAO);
        //std::cout << glGetError() << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
        //std::cout << glGetError() << std::endl;
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * stride * 2, positions, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //std::cout << glGetError() << std::endl;
    }
    shader->use();
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_FAN, 0, circle_pointNum+2);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
    //std::cout << glGetError() << std::endl;
    if (pocess > 0.03) isDrawing = false;
}

void painter::Node::getArc(GLfloat* data) {
    data[0] = x;
    data[1] = y;
    //data[31] = x;
    //data[32] = y;

    const int stride = circle_pointNum + 2;
    float scale = WindowParas::getInstance().defaultAlpha;
    float angle = 0;
    for (int i = 0; i <= circle_pointNum; i++) {
        angle = 2.0f * PI * i / circle_pointNum;
        data[i * 2 + 2 ] = x + pocess * cos(angle) / scale;
        data[i * 2 + 3] = y + pocess * sin(angle);
        //std::cout << data[i * 2] << ", " << data[i * 2 + 1] << std::endl;
    }

    //std::cout << std::endl;
}

painter::Edge::Edge(GLfloat* positions, GLint color, int v1, int v2, int satrt, Shader* shader)
    : shader(shader), start(start), isDrawing(true), poccess(0) {
    std::copy(positions, positions + 4, node);

    delta = 0.0002 / sqrt(pow(node[0] - node[2], 2) + pow(node[1] - node[3], 2));
    GLfloat position[8];
    transform(position);
    int colors[4] = { color };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, position, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4, colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, 1 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void painter::Edge::draw() {
    GLfloat position[8];
    if (isDrawing) {        
        transform(position);
    }
    shader->use();
    glBindVertexArray(VAO);
    //std::cout << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void painter::Edge::transform(GLfloat* position) {
    poccess += delta;
    
    GLfloat sX, sY, eX, eY;
    if (start == v1) {
        sX = node[0]; sY = node[1]; eX = sX + poccess * (node[2] - sX); eY = sY + poccess * (node[3] - sY);
    } else {
        sX = node[2]; sY = node[3]; eX = sX + poccess * (node[0] - sX); eY = sY + poccess * (node[1] - sY);
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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, position, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (poccess > 1) isDrawing = false;
}