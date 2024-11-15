#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <glm/glm.hpp>

#include "glad/gl.h"
#include "shader.hpp"

struct Vertex {
    glm::vec3 position{0.0f};
    glm::vec3 colour{0.0f};
    // glm::vec2 tex_coord;
};

class Model {
public:
    Model(std::vector<Vertex> &vertices, std::vector<GLushort> &indices, ShaderProgram &shader);

    void draw();
private:
    std::vector<Vertex> vertices{};
    std::vector<GLushort> indices{};

    ShaderProgram &shader;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    void prepare();
};

#endif