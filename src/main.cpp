#include "FractalCmdLine.h"

#include <stdlib.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

#define OPENGL_MIN_VERSION_MAJ 2
#define OPENGL_MIN_VERSION_MIN 0

static void glfw_error(int error, const char* description)
{
  fprintf(stderr, "error: glfw: %s\n", description);
}

static GLFWwindow* setupGlfw()
{
  if (!glfwInit())
  {
    printf("error: glfw init failed\n");
    exit(1);
  }

  glfwSetErrorCallback(glfw_error);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MIN_VERSION_MAJ);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MIN_VERSION_MIN);

  GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight,
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

  auto viewportProjection { glm::ortho(-2.0, 1.0, -1.0, 1.0) };

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

  GLFWwindow* window = setupGlfw();
  while (!glfwWindowShouldClose())
  {

  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
