#pragma once

#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "renderer.hpp"
#include "runtimedata.hpp"

class Window
{
public:
  Window();
  ~Window();

  int loop();
  void interface();

private:
  std::unique_ptr<Renderer> m_renderer;
  std::unique_ptr<RuntimeData> m_state;

  GLFWwindow* m_window = nullptr;
};
