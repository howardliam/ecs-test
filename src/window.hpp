#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_video.h>
#include <string>

#include <SDL2/SDL.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    bool is_running();
    void begin();
    void end();

    SDL_Window *get_window();
    SDL_GLContext get_context();
private:
    int width;
    int height;
    std::string title;

    bool running{true};

    SDL_Window *window;
    SDL_GLContext context;
};

#endif
