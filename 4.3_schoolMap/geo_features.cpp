#include"geo_features.h"

Building::Building(GLfloat x, GLfloat y, Shader* shader, std::string name): x(x), y(y), isSelected(false), shader(shader), name(name) {
    float vertices[] = {
           x-cubeSize/2, y- cubeSize / 2, 0.f,
            x+cubeSize / 2, y- cubeSize / 2, 0.f,
            x+ cubeSize / 2,  y+ cubeSize / 2, 0.f,
            x- cubeSize / 2,  y+ cubeSize / 2, 0.f,
             x- cubeSize / 2, y- cubeSize / 2,  cubeSize,
            x+ cubeSize / 2, y- cubeSize / 2,  cubeSize,
             x+ cubeSize / 2,  y+ cubeSize / 2,  cubeSize,
            x- cubeSize / 2,  y+ cubeSize / 2,  cubeSize
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // front face
        4, 5, 6, 6, 7, 4, // back face
        0, 1, 5, 5, 4, 0, // bottom face
        2, 3, 7, 7, 6, 2, // top face
        0, 3, 7, 7, 4, 0, // left face
        1, 2, 6, 6, 5, 1  // right face
    };
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Building::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}