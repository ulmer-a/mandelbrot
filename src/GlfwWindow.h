#pragma once

#include <cstddef>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GlfwWindow
{
  public:
    GlfwWindow(size_t width, size_t height, std::function<void()> loopHandler,
               const char* title = "OpenGL",
               int glMajorVersion = 2, int glMinorVersion = 0);
    ~GlfwWindow();

    void bind();

    void exec();

    static void prepare();
    static void destroy();

  private:
    GLFWwindow* m_window;
    std::function<void()> m_loopHandler;
};

