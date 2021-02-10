#pragma once

#include <CmdLineParser.h>
#include <string>

class ResCmdLineHandler : public CmdLine::CommandLineParser
{
    enum ResArguments
    {
      ArgInput,
      ArgOutput,
      ArgName
    };

  public:
    ResCmdLineHandler(int argc, char** argv);

    bool onOptionEncounter(int callbackId) override;

    const char* helpText(int callbackId) override;

    std::string getInputFile() const { return m_input; }
    std::string getOutputFile() const { return m_output; }
    std::string getIdentifier() const { return m_ident; }

  private:
    std::string m_input, m_output, m_ident;
};

