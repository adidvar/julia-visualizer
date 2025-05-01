#pragma once

#include "renderer.hpp"
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class Window
{
public:
  Window();
  ~Window();

  int loop();
  void interface();

  //GLFW events
  static void errorEvent(int error, const char * description);
  static void framBufferSizeEvent(GLFWwindow* window, int width, int height);

private:
  std::unique_ptr<Renderer> m_renderer;
  GLFWwindow *m_window = nullptr;
};
