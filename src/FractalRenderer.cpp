#include <GL/glew.h>

#include "FractalRenderer.h"
#include "ShaderProgram.h"
#include "GlfwWindow.h"
#include "ResourceManager.h"

extern const char* res_shader_vertex_default;
extern const char* res_shader_fragment_mandelbrot;

struct Vertex
{
  float x, y;
};

void FractalRenderer::setupVertexBuffer()
{
  const static Vertex vertexBuffer[] = {
    { -1.0,  1.0 },
    { -1.0, -1.0 },
    {  1.0,  1.0 },
    {  1.0, -1.0 },
    {  1.0,  1.0 },
    { -1.0, -1.0 }
  };

  unsigned int vertexBufferId;
  glGenBuffers(1, &vertexBufferId);
  glError();
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glError();
  glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertexBuffer, GL_STATIC_DRAW);
  glError();

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
  glError();
  glEnableVertexAttribArray(0);
  glError();
}

bool FractalRenderer::setup()
{
  m_shaderProgram = std::make_shared<ShaderProgram>();

  const std::string vertexShaderSrc = ResourceManager::getInstance()
      .loadString(res_shader_vertex_default);
  const std::string fragmentShaderSrc = ResourceManager::getInstance()
      .loadString(res_shader_fragment_mandelbrot);

  if (!m_shaderProgram->addVertexShader(vertexShaderSrc.c_str()))
    return false;
  if (!m_shaderProgram->addFragmentShader(fragmentShaderSrc.c_str()))
    return false;
  if (!m_shaderProgram->link())
    return false;
  m_shaderProgram->activate();

  setupVertexBuffer();
  return true;
}

void FractalRenderer::draw()
{
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
