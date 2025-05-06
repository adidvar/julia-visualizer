#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <wrappers/renderlist.hpp>
#include <wrappers/shader.hpp>

class Window
{
public:
  Window();
  virtual ~Window();

  virtual void handleMousePosition() = 0;
  virtual void handleMouseButton() = 0;
  virtual void handleMouseWheel() = 0;
  virtual void handleKeyboardKey() = 0;

protected:
  GLFWwindow* window_ = nullptr;
};
