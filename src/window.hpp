#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    bool should_close();
    void begin();
    void end();
private:
    int width;
    int height;
    std::string title;

    GLFWwindow *window;
};

#endif
