#include <cstdio>
#include <cstdlib>

#include "ResCmdLineHandler.h"

extern char *base64_encode(const unsigned char *data,
                           size_t input_length,
                           size_t *output_length);

static FILE* openFile(const std::string& file,
                      const char* mode,
                      FILE* defaultFile)
{
  if (file.length() < 1)
    return defaultFile;

  FILE* f = fopen(file.c_str(), mode);
  if (f == NULL)
  {
    printf("%s: cannot open file\n", file.c_str());
    exit(1);
  }
  return f;
}

static char* loadFile(const std::string& fileName, size_t& size)
{
  FILE* f = fopen(fileName.c_str(), "rb");

  if (f == nullptr)
  {
    printf("%s: cannot open file\n", fileName.c_str());
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);

  char* buffer = new char[size];
  fread(buffer, 1, size, f);
  return buffer;
}

int main(int argc, char* argv[])
{
  ResCmdLineHandler cmdLine(argc, argv);
  if (!cmdLine.parse())
  {
    printf("%s\n", cmdLine.getError());
    exit(1);
  }

  std::string resourceFileName = cmdLine.getInputFile();
  std::string outputFileName = cmdLine.getOutputFile();
  FILE* outFd = openFile(outputFileName, "w+", stdout);

  std::string basePath = resourceFileName.substr(0,
                          resourceFileName.find_last_of("/\\") + 1);

  size_t resourceFileSize;
  std::string resourceFile(loadFile(resourceFileName, resourceFileSize));

  std::vector<std::pair<std::string, std::string>> files;

  auto processLine = [&files, &basePath](std::string line) {
    size_t pos = line.find(':');
    files.emplace_back(
      basePath + line.substr(0, pos),
      line.substr(pos+1)
    );
  };

  size_t pos;
  while ((pos = resourceFile.find('\n')) != std::string::npos)
  {
    processLine(resourceFile.substr(0, pos));
    resourceFile = resourceFile.substr(pos + 1);
  }

  for (auto& file : files)
  {
    std::string& fileName = file.first;
    std::string& identifier = file.second;

    size_t fileSize;
    char* fileContent = loadFile(fileName, fileSize);

    char* outBuffer = base64_encode((unsigned char*)fileContent, fileSize, &fileSize);

    fprintf(outFd, "const char* res_%s = \"%s\";\n", identifier.c_str(), outBuffer);

    delete(fileContent);
    free(outBuffer);
  }
}
