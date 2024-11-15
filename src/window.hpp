#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <chrono>

#include <SDL3/SDL.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    void poll_events(); // Poll SDL events for stuff
    void begin(); // Prepare for rendering (mainly imgui)
    void end(); // End render

    int get_width();
    int get_height();
    float get_aspect_ratio();
    void set_title(std::string new_title);

    bool is_open();

    SDL_Window *get_window();
    SDL_GLContext get_context();

    float get_frame_time();
    float get_fps();
private:
    int width;
    int height;
    std::string title;

    bool open{true};

    SDL_Window *window;
    SDL_GLContext context;

    std::chrono::time_point<std::chrono::high_resolution_clock> current_time;
    float frame_time;

    void initialise_sdl();
    void set_attributes();
    void setup_window();
    void setup_opengl();
    void setup_imgui();
};

#endif
