#version 330 core
layout(location = 0) in vec3 aPos;   // from VBO
layout(location = 1) in vec3 aColor; // from VBO

out vec3 ourColor; // pass to fragment shader
uniform mat4 transform;
void main() {
  gl_Position = transform * vec4(aPos, 1.0);
  ourColor = aColor;
}
