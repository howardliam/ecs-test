#include <cstdlib>

#include "glad/gl.h"

#include "imgui/imgui.h"
#include "shader.hpp"
#include "window.hpp"
#include "model.hpp"

int main() {
    Window window{1600, 900, "Test Window"};

    ShaderProgram shader{"assets/shaders/shader.vert", "assets/shaders/shader.frag"};

    std::vector<Vertex> vertices{
        {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
    };

    std::vector<GLushort> indices{
        0, 1, 2
    };

    Model shape{vertices, indices, shader};

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // GLfloat vertices[] {
    //     0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    // };

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);

    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    bool open = false;
    while(window.is_running()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.poll_events();

        window.begin();

        ImGui::ShowDemoWindow(&open);

        // shader.bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // shader.unbind();

        shape.draw();

        window.end();
    }

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

    // glBindVertexArray(0);

    return EXIT_SUCCESS;
}
