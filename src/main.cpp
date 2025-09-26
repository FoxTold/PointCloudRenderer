#include "Renderer.h"
#include "Triangle.h"
int main(void) {
  auto renderer = Renderer();
  renderer.addTriangle();
  while (!renderer.shouldClose()) {
    renderer.render();
  }
}