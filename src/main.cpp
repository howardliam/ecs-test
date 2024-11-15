#include <cstdlib>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"
#include "imgui/imgui.h"
#include "shader.hpp"
#include "window.hpp"
#include "model.hpp"

int main() {
    Window window{1600, 900, "Test Window"};

    ShaderProgram shader{"assets/shaders/shader.vert", "assets/shaders/shader.frag"};

    std::vector<Vertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    };

    std::vector<GLushort> indices{
        0, 1, 2,
        2, 3, 0,
    };

    Model shape{vertices, indices, shader};

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.7778f, 0.01f, 100.0f);
    shader.load_projection_matrix(projection);

    glm::mat4 model(1.0f);
    model = glm::translate(model, {0.0f, 0.0f, -10.0f});
    shader.load_model_matrix(model);

    bool open = false;
    while(window.is_open()) {
        window.poll_events();
        window.begin();



        ImGui::ShowDemoWindow(&open);

        shape.draw();



        window.end();
    }

    return EXIT_SUCCESS;
}
