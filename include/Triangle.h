#pragma once
#include "Vertex.h"
#include "glad/glad.h"
#include <vector>
class Triangle {
public:
  Triangle();
  void init();
  void render();
  void rotate();

private:
  std::vector<Vertex> vertexes;
  unsigned int VAO, VBO, EBO;
  unsigned int _shaderProgram;

private:
  void linkShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};