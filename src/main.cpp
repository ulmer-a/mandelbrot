#include "FractalCmdLine.h"

int main(int argc, char* argv[])
{
  Fractal::FractalCmdLine cmdLineHandler {argc, argv};

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

  return 0;
}
