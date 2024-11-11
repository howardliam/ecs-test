#include "window.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>

#include "gl.h"

Window::Window(int width, int height, const char *title) : width{width}, height{height}, title{title} {
    int res = SDL_Init(SDL_INIT_VIDEO);
    if (res != 0) {
        auto err = SDL_GetError();
        std::cerr << "Failed to initialise SDL: " << err << "\n";
        exit(1);
    }
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

    auto pos = SDL_WINDOWPOS_UNDEFINED;
    auto flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(title, pos, pos, width, height, flags);
    if (!window) {
        auto err = SDL_GetError();
        std::cerr << "Failed to create window: " << err << "\n";
        exit(1);
    }

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

Window::~Window() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::is_running() {
    return running;
}

void Window::begin() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;
            glViewport(0, 0, newWidth, newHeight);
        }
    }
}

void Window::end() {
    SDL_GL_SwapWindow(window);
}

SDL_Window *Window::get_window() {
    return window;
}

SDL_GLContext Window::get_context() {
    return context;
}
