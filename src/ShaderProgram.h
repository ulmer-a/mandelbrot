#pragma once

#include <string>
#include <vector>

class ShaderProgram
{
  public:
    ShaderProgram();
    ~ShaderProgram();

    bool addVertexShader(const char* source);
    bool addFragmentShader(const char* source);

    bool link();
    bool activate();

    int getUniform(const std::string &uniform);

  private:
    bool addShader(int type, const char* source);

  private:
    unsigned int m_shaderProgram;
    std::vector<unsigned int> m_shaders;
};
