#include "FractalCmdLine.h"

Fractal::FractalCmdLine::FractalCmdLine(int argc, char **argv)
  : CmdLine::CommandLineParser(argc, argv)
{
}

void Fractal::FractalCmdLine::handleHelpText(std::function<void ()> handler)
{
  expectFlag('h', ArgHelp);
  expectLongFlag("help", ArgHelp);

  m_helpHandler = handler;
}

void Fractal::FractalCmdLine::handleVersionInfo(std::function<void ()> handler)
{
  expectFlag('v', ArgVersion);
  expectLongFlag("version", ArgVersion);

  m_versionHandler = handler;
}

bool Fractal::FractalCmdLine::onOptionEncounter(int callbackId)
{
  switch (callbackId)
  {
  case ArgHelp:
    m_helpHandler();
    break;
  case ArgVersion:
    m_versionHandler();
    break;
  }

  return true;
}

const char *Fractal::FractalCmdLine::helpText(int callbackId)
{
  switch (callbackId)
  {
  case ArgHelp:
    return "print this help text";
  case ArgVersion:
    return "print version information";
  default:
    return nullptr;
  }
}
