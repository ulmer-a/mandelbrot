#include "ResourceManager.h"

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager &ResourceManager::getInstance()
{
  if (s_instance == nullptr)
    s_instance = new ResourceManager();
  return *s_instance;
}

ResourceManager::ResourceManager()
{

}

std::string ResourceManager::getString(const std::string &name)
{
  return std::string();
}
