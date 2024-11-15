#include "window.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL3/SDL_video.h>

#include "glad/gl.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_opengl3.h"

Window::Window(int width, int height, const char *title) : width{width}, height{height}, title{title} {
    initialise_sdl();
    set_attributes();
    setup_window();
    setup_opengl();
    setup_imgui();

    current_time = std::chrono::high_resolution_clock::now();
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            open = false;
            break;
        } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;
            glViewport(0, 0, newWidth, newHeight);
            width = newWidth;
            height = newHeight;
        }
    }
}

void Window::begin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    auto new_time = std::chrono::high_resolution_clock::now();
    frame_time = std::chrono::duration<float, std::chrono::seconds::period>(new_time - current_time).count();
    current_time = new_time;
}

void Window::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

int Window::get_width() {
    return width;
}

int Window::get_height() {
    return height;
}

float Window::get_aspect_ratio() {
    return static_cast<float>(width) / height;
}

void Window::set_title(std::string new_title) {
    title = new_title;
    SDL_SetWindowTitle(window, title.c_str());
}

bool Window::is_open() {
    return open;
}

SDL_Window *Window::get_window() {
    return window;
}

SDL_GLContext Window::get_context() {
    return context;
}

float Window::get_frame_time() {
    return frame_time;
}

float Window::get_fps() {
    return 1.0f / frame_time;
}

void Window::initialise_sdl() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        auto err = SDL_GetError();
        std::cerr << "Failed to initialise SDL: " << err << "\n";
        exit(1);
    }
}

void Window::set_attributes() {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

void Window::setup_window() {
    auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(title.c_str(), width, height, flags);
    if (!window) {
        auto err = SDL_GetError();
        std::cerr << "Failed to create window: " << err << "\n";
        exit(1);
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::setup_opengl() {
    context = SDL_GL_CreateContext(window);
    if (!context) {
        auto err = SDL_GetError();
        std::cerr << "Failed to create context: " << err << "\n";
        exit(1);
    }

    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
}

void Window::setup_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(get_window(), get_context());
    ImGui_ImplOpenGL3_Init("#version 460 core");
}
