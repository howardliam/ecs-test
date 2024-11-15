#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    void poll_events(); // Poll SDL events for stuff
    void begin(); // Prepare for rendering (mainly imgui)
    void end(); // End render

    bool is_running();
    SDL_Window *get_window();
    SDL_GLContext get_context();
private:
    int width;
    int height;
    std::string title;

    bool running{true};

    SDL_Window *window;
    SDL_GLContext context;

    void initialise_sdl();
    void set_attributes();
    void setup_window();
    void setup_opengl();
    void setup_imgui();
};

#endif
