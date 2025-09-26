#include "Triangle.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

#include <string>
std::string loadShaderSource(const char *filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open shader file: " << filepath << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf(); // read the whole file into the stream
  return buffer.str();
}

GLuint compileShader(const char *filepath, GLenum type) {
  std::string code = loadShaderSource(filepath);
  if (code.empty())
    return 0;

  const char *source = code.c_str();

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED in " << filepath << "\n"
              << infoLog << std::endl;
  }
  return shader;
}
void Triangle::linkShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
  int success;
  char infoLog[512];
  _shaderProgram = glCreateProgram();
  glAttachShader(_shaderProgram, vertexShader);
  glAttachShader(_shaderProgram, fragmentShader);
  glLinkProgram(_shaderProgram);
  glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Triangle::Triangle() {
  auto vertex = Vertex();

  // fill vertices
  vertex.pos = {-0.5f, -0.5f, 0.0f};
  vertex.rgb = {1.f, 0.f, 0.f};
  vertexes.push_back(vertex);

  vertex.pos = {0.5f, -0.5f, 0.0f};
  vertex.rgb = {0.f, 1.f, 0.f};
  vertexes.push_back(vertex);

  vertex.pos = {0.0f, 0.5f, 0.0f};
  vertex.rgb = {0.f, 0.f, 1.f};
  vertexes.push_back(vertex);

  // compile shaders
  auto fragmentShader =
      compileShader("/home/riba/dev/PointCloudRenderer/shaders/shader.frag",
                    GL_FRAGMENT_SHADER);
  auto vertexShader =
      compileShader("/home/riba/dev/PointCloudRenderer/shaders/shader.vert",
                    GL_VERTEX_SHADER);
  linkShaderProgram(vertexShader, fragmentShader);

  // upload vertex data
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // use sizeof(Vertex), not sizeof(float)
  glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(Vertex),
               vertexes.data(), GL_STATIC_DRAW);

  // position attribute (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));
  glEnableVertexAttribArray(0);

  // color attribute (location = 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, rgb));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

void Triangle::render() {
  glUseProgram(_shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Triangle::rotate() {
  float time = glfwGetTime(); // seconds since program start
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, time * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

  unsigned int transformLoc = glGetUniformLocation(_shaderProgram, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}
