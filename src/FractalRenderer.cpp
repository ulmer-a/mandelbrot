#include "FractalRenderer.h"
#include "GlfwWindow.h"

#include <GL/glew.h>

struct Vertex
{
  float x, y, z;
};

FractalRenderer::FractalRenderer()
{

}

void FractalRenderer::setup()
{
  /*const static Vertex vertexBuffer[] = {
    { 0.5,  0.5, 0.0 },
    { -0.5, -0.5, 0.0 },
    {  0.5 -0.5, 0.0 }
  };

  unsigned int vertexBufferId;
  glGenBuffers(1, &vertexBufferId);
  glError();
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glError()
  glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertexBuffer, GL_STATIC_DRAW);
  glError()

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
  glError()
  glEnableVertexAttribArray(0);
  glError()*/
}

void FractalRenderer::draw()
{
  glBegin(GL_TRIANGLES);
  glColor3f(0.1f, 0.2f, 0.8f);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);
  glVertex3f(0, 1, 0);
  glEnd();
}
