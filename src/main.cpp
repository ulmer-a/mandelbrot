#include <stdlib.h>

#include "GlfwWindow.h"
#include "FractalRenderer.h"
#include "FractalCmdLine.h"

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

  FractalRenderer fractal;
  GlfwWindow window(width, height, [&fractal]() {
    fractal.draw();
  });
  fractal.setup();
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  window.exec();
  return 0;
}
