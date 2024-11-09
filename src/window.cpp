#include "window.hpp"
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char *title) : width{width}, height{height}, title{title} {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::begin() {
    glfwPollEvents();
}

void Window::end() {
    glfwSwapBuffers(window);
}
