#include "GlfwWindow.h"

#include <cstdlib>
#include <cstdio>



GlfwWindow::GlfwWindow(size_t width, size_t height,
                       std::function<void()> loopHandler,
                       const char *title,
                       int glMajorVersion, int glMinorVersion)
  : m_closed(false)
  , m_loopHandler(loopHandler)
{
  prepare();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glError();

  m_window = glfwCreateWindow(width, height,
                          title, nullptr, nullptr);
  if (!m_window)
  {
    fprintf(stderr, "error: window creation failed\n");
    exit(1);
  }

  bind();

  GLenum err;
  if ((err = glewInit()) != GLEW_OK)
  {
    fprintf(stderr, "error: glew: %s\n", glewGetErrorString(err));
    exit(1);
  }
  glError();

  int fb_width, fb_height;
  glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(m_window);
  destroy();
}

void GlfwWindow::bind()
{
  glfwMakeContextCurrent(m_window);
}

void GlfwWindow::exec()
{
  while (!glfwWindowShouldClose(m_window))
  {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_loopHandler();
  }
}

static void glfw_error(int error, const char* description)
{
  (void)error;
  fprintf(stderr, "error: glfw: %s\n", description);
}

void GlfwWindow::prepare()
{
  if (!glfwInit())
  {
    printf("error: glfw init failed\n");
    exit(1);
  }

  glfwSetErrorCallback(glfw_error);
}

void GlfwWindow::destroy()
{
  glfwTerminate();
}
