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
  auto mainLoop = [&fractal]() {
    fractal.draw();
  };

  // setup a window with OpenGL context
  GlfwWindow window(width, height, mainLoop);

  // setup fractal Renderer (fragment shader)
  if (!fractal.setup())
  {
    printf("FractalRenderer setup failed\n");
    return 1;
  }

  // run the program
  window.exec();
  return 0;
}
