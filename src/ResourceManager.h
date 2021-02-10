#pragma once

#include <string>

class ResourceManager
{
  public:
    static ResourceManager& getInstance();

    std::string getString(const std::string& name);

  private:
    static ResourceManager* s_instance;

  private:
    ResourceManager();
};

