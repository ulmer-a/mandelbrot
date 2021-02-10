#pragma once

#include <memory>

#include "ShaderProgram.h"

class FractalRenderer
{
  public:
    FractalRenderer() = default;

    bool setup();

    void draw();

  private:
    void setupVertexBuffer();

  private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
};

