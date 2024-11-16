#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    void poll_events(); // Poll SDL events for stuff
    void begin(); // Prepare for rendering (mainly imgui)
    void end(); // End render

    int get_width() { return width; }
    int get_height() { return height; }
    float get_aspect_ratio() { return static_cast<float>(width) / height; }
    void set_title(std::string new_title) {
        title = new_title;
        SDL_SetWindowTitle(window, title.c_str());
    }

    SDL_Window *get_window() { return window; }
    SDL_GLContext get_context() { return context; }
    void toggle_fullscreen() {
        fullscreen = !fullscreen;
        SDL_SetWindowFullscreen(window, fullscreen);
    }

    bool is_open() { return open; }
    void set_window_to_close() { open = false; }

    float get_frame_time() { return frame_time; }
    float get_fps() { return 1.0f / frame_time; }

    bool is_key_down(SDL_Scancode key) {
        if (std::find(keys_pressed.begin(), keys_pressed.end(), key) != keys_pressed.end()) {
            return true;
        }
        return false;
    }
private:
    int width;
    int height;
    std::string title;

    SDL_Window *window;
    SDL_GLContext context;
    bool fullscreen{false};

    bool open{true};

    std::chrono::time_point<std::chrono::high_resolution_clock> current_time;
    float frame_time;

    std::vector<int> keys_pressed{};

    void initialise_sdl();
    void set_attributes();
    void setup_window();
    void setup_opengl();
    void setup_imgui();
};

#endif
