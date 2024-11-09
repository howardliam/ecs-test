#include "shader.hpp"

#include <vector>
#include <fstream>
#include <iostream>

std::vector<char> load_shader(const char *file_name) {
    std::ifstream file{file_name, std::ios::ate};

    size_t file_size = file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);

    file.close();

    return buffer;
}

ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
    vertex_shader = create_shader(GL_VERTEX_SHADER, vertexPath);
    fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragmentPath);
    shader_program = create_program();
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glDeleteProgram(shader_program);
}

void ShaderProgram::bind() {
    glUseProgram(shader_program);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

GLuint ShaderProgram::create_shader(GLenum shader_type, const char *path) {
    auto code = load_shader(path);
    auto data = code.data();
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &data, nullptr);
    glCompileShader(shader);

    GLint result = GL_FALSE;
    int info_log_length;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

    if (!result) {
        std::vector<char> message(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, nullptr, &message[0]);

        std::cout << "Shader: " << path << "\n";
        std::cout << message.data() << "\n";
    }

    return shader;
}

GLuint ShaderProgram::create_program() {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    return program;
}
