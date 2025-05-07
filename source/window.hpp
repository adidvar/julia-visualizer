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

  void enableCaptureMouse(bool enabled) { enabled_mouse_capture_ = enabled; }

  void enableCaptureKeyboard(bool enabled)
  {
    enabled_keyboard_capture_ = enabled;
  }

  bool isMouseCaptureEnabled() const { return enabled_mouse_capture_; }

  bool isKeyboardCaptureEnabled() const { return enabled_keyboard_capture_; }

  static Window* getHandle(void*);

  void updateWindowRatio(int width, int height);

protected:
  GLFWwindow* window_ = nullptr;

  float window_ratio_ = 1;

  bool enabled_mouse_capture_ = true;
  bool enabled_keyboard_capture_ = true;
};
