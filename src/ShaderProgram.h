#pragma once

#include <string>
#include <vector>

class ShaderProgram
{
  public:
    ShaderProgram();
    ~ShaderProgram();

    bool addVertexShader(const std::string& file);
    bool addFragmentShader(const std::string& file);

    bool link();
    void activate();

    int getUniform(const std::string &uniform);

  private:
    bool addShader(int type, const std::string& name);

  private:
    unsigned int m_shaderProgram;
    std::vector<unsigned int> m_shaders;
};
