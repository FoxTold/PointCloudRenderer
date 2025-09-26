#include "Renderer.h"
#include "GLFW/glfw3.h"
#include "Triangle.h"
#include <sstream>
Renderer::Renderer() {
  initGLFW();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::logic_error("Failed to load glad");
  }
}

Renderer::~Renderer() { glfwTerminate(); }

bool Renderer::shouldClose() { return glfwWindowShouldClose(_window); }

void Renderer::initGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (_window == NULL) {
    glfwTerminate();
    throw std::logic_error("Failed to load glfw");
  }

  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window,
                                 [](GLFWwindow *window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });
}

void Renderer::render() {
  processInput();
  clearWindow();

  for (auto &triangle : _triangles) {
    triangle.render();
  }

  handleFpsCounter();
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void Renderer::addTriangle() { _triangles.push_back(Triangle()); }

void Renderer::processInput() {
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(_window, true);
}

void Renderer::handleFpsCounter() {
  double currentTime = glfwGetTime();
  fps.frames++;
  if (currentTime - fps.lastTime >= 1.0) { // update every second
    std::ostringstream title;
    title << "OpenGL Window - FPS: " << fps.frames;
    glfwSetWindowTitle(_window, title.str().c_str());
    fps.frames = 0;
    fps.lastTime = currentTime;
  }
}

void Renderer::clearWindow() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT);
}
