#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Triangle.h"
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

class Renderer {
public:
  Renderer();
  ~Renderer();
  bool shouldClose();
  void render();
  void addTriangle();

private:
  void initGLFW();
  void processInput();
  void handleFpsCounter();
  void clearWindow();

private:
  GLFWwindow *_window;

  struct {
    double lastTime = glfwGetTime();
    int frames = 0;
  } fps;
  std::vector<Triangle> _triangles;
};
