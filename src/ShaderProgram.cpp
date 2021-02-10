#include <GL/glew.h>
#include <cassert>

#ifdef WIN32
#include <crtdbg.h>
#endif

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

bool ShaderProgram::addVertexShader(const char* source)
{
  return addShader(GL_VERTEX_SHADER, source);
}

bool ShaderProgram::addFragmentShader(const char* source)
{
  return addShader(GL_FRAGMENT_SHADER, source);
}

bool ShaderProgram::addShader(int type, const char* source)
{
  const char* shaderSourcePtr = source;

  unsigned int shaderId = glCreateShader(type);
  printf("compiling shader: id=%u\n", shaderId);
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
    printf("failed to compile shader (%u)\n%s\n",
           shaderId, message);
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

bool ShaderProgram::activate()
{
  glClearError();
  glUseProgram(m_shaderProgram);
  GLenum err;
  while((err = glGetError()) != GL_NO_ERROR)
  {
    printf("error: glUseProgram() failed: %u\n", err);
    return false;
  }
  printf("binding shader program: id=%u\n", m_shaderProgram);
  return true;
}

int ShaderProgram::getUniform(const std::string &uniform)
{
  return glGetUniformLocation(m_shaderProgram, uniform.c_str());
}
