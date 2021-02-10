#pragma once

#include <cstddef>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static GLenum err;

#define glError() \
    while((err = glGetError()) != GL_NO_ERROR){ \
        std::cout << __FILE__ ": " << __LINE__ << " (" << err << ")"; \
    } \
    exit(1);

class GlfwWindow
{
  public:
    GlfwWindow(size_t width, size_t height, std::function<void()> loopHandler,
               const char* title = "OpenGL",
               int glMajorVersion = 4, int glMinorVersion = 0);
    ~GlfwWindow();

    void bind();
    void exec();

  private:
    static void prepare();
    static void destroy();

  private:
    bool m_closed;
    GLFWwindow* m_window;
    std::function<void()> m_loopHandler;
};

