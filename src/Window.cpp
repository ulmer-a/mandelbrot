#include <cassert>
#include <stdlib.h>

#include "Window.h"

Window::Window()
{
  m_window = glfwCreateWindow(windowWidth, windowHeight,
                          "ULMER OpenGL fractal", nullptr, nullptr);
  if (!window)
  {
    fprintf(stderr, "error: window creation failed\n");
    exit(1);
  }
}

Window::~Window()
{
  glfwDestroyWindow(m_window);
}
