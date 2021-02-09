#include "FractalCmdLine.h"

#include <stdlib.h>

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

#define OPENGL_MIN_VERSION_MAJ 2
#define OPENGL_MIN_VERSION_MIN 0

static void glfw_error(int error, const char* description)
{
  fprintf(stderr, "error: glfw: %s\n", description);
}

static GLFWwindow* setupGlfw(size_t width, size_t height)
{
  if (!glfwInit())
  {
    printf("error: glfw init failed\n");
    exit(1);
  }

  glfwSetErrorCallback(glfw_error);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MIN_VERSION_MAJ);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MIN_VERSION_MIN);

  GLFWwindow* window = glfwCreateWindow(width, height,
                          "ULMER OpenGL fractal", nullptr, nullptr);
  if (!window)
  {
    fprintf(stderr, "error: window creation failed\n");
    exit(1);
  }

  return window;
}

int main(int argc, char* argv[])
{
  Fractal::FractalCmdLine cmdLineHandler {argc, argv};
  size_t width = 800, height = 600;

  cmdLineHandler.handleHelpText([&cmdLineHandler](){
    cmdLineHandler.printArgumentChoices();
    exit(0);
  });

  cmdLineHandler.handleVersionInfo([](){
    printf("FractalRenderer verison xyz\n"
           "Written by Alexander Ulmer\n\n");
    exit(0);
  });

  if (!cmdLineHandler.parse())
  {
    printf("%s\n", cmdLineHandler.getError());
    return 1;
  }

  glewInit();

  GLFWwindow* window = setupGlfw(width, height);
  while (!glfwWindowShouldClose(window))
  {

  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
