#include <cstdlib>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_scancode.h>

#include "glad/gl.h"
#include "imgui/imgui.h"
#include "shader.hpp"
#include "window.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "framebuffer.hpp"

#define WIDTH 1600
#define HEIGHT 900

int main() {
    Window window{WIDTH, HEIGHT, "Test Window"};

    ShaderProgram shader{"assets/shaders/shader.vert", "assets/shaders/shader.frag"};
    std::vector<Vertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}}, // bot left
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}}, // bot right
        {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}}, // top right
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}, // top left
    };
    std::vector<GLushort> indices{
        0, 1, 2,
        2, 3, 0,
    };
    Model shape{vertices, indices, shader};

#define USE_FRAMEBUFFER

#ifdef USE_FRAMEBUFFER
    ShaderProgram fb_shader{"assets/shaders/framebuffer.vert", "assets/shaders/framebuffer.frag"};
    std::vector<Vertex> fb_vertices{
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    };
    std::vector<GLushort> fb_indices{
        0, 1, 2,
        2, 3, 0,
    };
    Model fb_rect{vertices, indices, fb_shader};

    int fb_width, fb_height;
    SDL_GetWindowSizeInPixels(window.get_window(), &fb_width, &fb_height);

    Framebuffer framebuffer{fb_width, fb_height};
#endif



    Texture texture{"assets/textures/test_texture.png"};

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 model(1.0f);
    model = glm::translate(model, {0.0f, 0.0f, -1.0f});

    bool display_debug_info{true};

    while(window.is_open()) {
#ifdef USE_FRAMEBUFFER
        framebuffer.bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#endif

        window.poll_events();
        window.begin();

        if (window.is_key_down(SDL_SCANCODE_ESCAPE)) {
            window.set_window_to_close();
        }

        if (window.is_key_down(SDL_SCANCODE_F11)) {
            window.toggle_fullscreen();
        }

        if (window.is_key_down(SDL_SCANCODE_F3)) {
            display_debug_info = !display_debug_info;
        }

        if (display_debug_info) {
            ImGui::Begin("Debug (F3 to toggle)", &display_debug_info, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("%d FPS", static_cast<int>(window.get_fps()));
            ImGui::Text("%f ms per frame", window.get_frame_time() * 1000);
            ImGui::End();
        }

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.get_aspect_ratio(), 0.001f, 100.0f);
        shader.load_projection_matrix(projection);

        model = glm::rotate(model, glm::radians(1.0f), {1.0f, 1.0f, 1.0f});
        shader.load_model_matrix(model);

        texture.bind();
        shape.draw();
        texture.unbind();

#ifdef USE_FRAMEBUFFER
        framebuffer.unbind();
        glDisable(GL_DEPTH_TEST);
        framebuffer.bind_texture();
        fb_rect.draw();
        framebuffer.unbind_texture();
#endif

        window.end();
    }

    return EXIT_SUCCESS;
}
