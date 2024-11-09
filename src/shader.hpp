#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram(const char *vertexPath, const char *fragmentPath);
    ~ShaderProgram();

    void bind();
    void unbind();
private:
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;

    GLuint create_shader(GLenum shader_type, const char *path);
    GLuint create_program();
};

#endif
