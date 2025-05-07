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

  virtual void handleMousePosition(double cursor_x, double cursor_y) = 0;
  virtual void handleMouseButton(int button, int action, int mods) = 0;
  virtual void handleMouseWheel(double wheel_x, double wheel_y) = 0;
  virtual void handleKeyboardKey(int key,
                                 int scancode,
                                 int action,
                                 int mods) = 0;

  static Window* getHandle(void*);

  void updateWindowRatio(int width, int height);

protected:
  GLFWwindow* window_ = nullptr;

  float window_ratio_ = 1;
};
