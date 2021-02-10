#include "ResCmdLineHandler.h"

ResCmdLineHandler::ResCmdLineHandler(int argc, char **argv)
  : CmdLine::CommandLineParser(argc, argv)
{
  expectFlag('i', ArgInput, ArgumentType::StringArgument);
  expectFlag('o', ArgOutput, ArgumentType::StringArgument);
  expectFlag('n', ArgName, ArgumentType::StringArgument);
}

bool ResCmdLineHandler::onOptionEncounter(int callbackId)
{
  switch (callbackId)
  {
  case ArgInput:
    m_input = getStringParameter();
    break;
  case ArgOutput:
    m_output = getStringParameter();
    break;
  case ArgName:
    m_ident = getStringParameter();
    break;
  default: return false;
  }

  return true;
}

const char *ResCmdLineHandler::helpText(int callbackId)
{
  switch (callbackId)
  {
  case ArgInput: return "input file (binary)";
  case ArgOutput: return "output file (.cpp)";
  case ArgName: return "identifier";
  default: return nullptr;
  }
}
