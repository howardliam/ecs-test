#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include "glad/gl.h"

class ShaderProgram {
public:
    ShaderProgram(const char *vertexPath, const char *fragmentPath);
    ~ShaderProgram();

    void bind();
    void unbind();

    void load_projection_matrix(glm::mat4 matrix);
    void load_view_matrix(glm::mat4 matrix);
    void load_model_matrix(glm::mat4 matrix);
private:
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;

    GLuint create_shader(GLenum shader_type, const char *path);
    GLuint create_program();

    void load_matrix(glm::mat4 matrix, const char *uniform_name);
};

#endif
