#pragma once

#include <GLFW/glfw3.h>

class Window
{
  public:
    Window();
    ~Window();

  private:
    GLFWwindow* m_window;
};

