#include <GL/glew.h>
#include <cassert>

#include "ShaderProgram.h"
#include "ResourceManager.h"

#define glClearError() while (glGetError() != GL_NO_ERROR);

ShaderProgram::ShaderProgram()
  : m_shaderProgram(glCreateProgram())
{ }

ShaderProgram::~ShaderProgram()
{
  glDeleteProgram(m_shaderProgram);
}

bool ShaderProgram::addVertexShader(const std::string &file)
{
  return addShader(GL_VERTEX_SHADER, file);
}

bool ShaderProgram::addFragmentShader(const std::string &file)
{
  return addShader(GL_FRAGMENT_SHADER, file);
}

bool ShaderProgram::addShader(int type, const std::string& name)
{
  std::string shaderSource(ResourceManager::getInstance().getString(name));
  const char* shaderSourcePtr = shaderSource.c_str();
  if (shaderSource.size() < 1)
  {
    printf("error: %s: invalid shader source provided\n", name.c_str());
    return false;
  }

  unsigned int shaderId = glCreateShader(type);
  printf("compiling shader: name=%s, id=%u\n", name.c_str(), shaderId);
  glShaderSource(shaderId, 1, &shaderSourcePtr, NULL);
  glCompileShader(shaderId);

  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    int length;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length);
    glGetShaderInfoLog(shaderId, 512, NULL, message);
    printf("failed to compile shader '%s' (%u)\n%s\n",
           name.c_str(), shaderId, message);
    return false;
    glDeleteShader(shaderId);
  }

  m_shaders.push_back(shaderId);
  return true;
}

bool ShaderProgram::link()
{
  for (auto shaderId : m_shaders)
    glAttachShader(m_shaderProgram, shaderId);

  glClearError();
  glLinkProgram(m_shaderProgram);

  int success;
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

  printf("linking shader program: id=%u\n", m_shaderProgram);
  if(!success)
  {
    int length;
    glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length);
    glGetProgramInfoLog(m_shaderProgram, 512, NULL, message);
    printf("shader program linkage failed: id=%u\n%s\n",
           m_shaderProgram, message);
    return false;
  }

  return true;
}

void ShaderProgram::activate()
{
  glClearError();
  glUseProgram(m_shaderProgram);
  GLenum err;
  while((err = glGetError()) != GL_NO_ERROR)
  {
    printf("error: glUseProgram() failed: %u\n", err);
    assert(false && "shader program binding failed");
  }
  printf("binding shader program: id=%u\n", m_shaderProgram);
}

int ShaderProgram::getUniform(const std::string &uniform)
{
  return glGetUniformLocation(m_shaderProgram, uniform.c_str());
}
