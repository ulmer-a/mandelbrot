#pragma once

#include <string>
#include <memory>
#include <map>

class ResourceManager
{
  public:
    static ResourceManager& getInstance();
    std::string getString(const std::string& name);

    std::string loadString(const char* data);

  private:
    static ResourceManager* s_instance;

  private:
    ResourceManager();
};

