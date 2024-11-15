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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    bool open = false;
    while(window.is_running()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.poll_events();

        window.begin();

        ImGui::ShowDemoWindow(&open);

        shape.draw();

        window.end();
    }

    return EXIT_SUCCESS;
}
