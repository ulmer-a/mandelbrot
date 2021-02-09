#include <CmdLineParser.h>

#include <functional>

namespace Fractal {

  class FractalCmdLine : public CmdLine::CommandLineParser
  {
    private:
      enum FractalArguments
      {
          ArgHelp,
          ArgVersion
      };

    public:
      FractalCmdLine(int argc, char** argv);

      void handleHelpText(std::function<void()> handler);
      void handleVersionInfo(std::function<void()> handler);

    protected:
      bool onOptionEncounter(int callbackId) final;
      const char* helpText(int callbackId) final;

    private:
      std::function<void()> m_helpHandler;
      std::function<void()> m_versionHandler;
  };

}


