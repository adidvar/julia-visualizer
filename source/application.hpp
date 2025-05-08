#pragma once

#include <memory>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include "window.hpp"
#include "wrappers/renderlist.hpp"
#include "wrappers/shader.hpp"

class Application : public Window
{
public:
  Application();
  ~Application() override;

  int run();

  void renderGUI();
  void renderBackground();

  void processsInput();

  void handleMousePosition(double cursor_x, double cursor_y) override
  {
    // std::cout << "CURSOR::" << cursor_x << ":::" << cursor_y << std::endl;
    if (movement_mode_) {
      window_start_x_ += 0.01 * (cursor_x_ - cursor_x);
      window_start_y_ += 0.01 * (cursor_y_ - cursor_y);

      cursor_x_ = cursor_x;
      cursor_y_ = cursor_y;
    }
  }

  void handleMouseButton(int button, int action, int mods) override
  {
    // std::cout << "MOUSE::" << button << ":::" << action << ":::" << mods <<
    // std::endl;
    if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) {
      movement_mode_ = (action == GLFW_PRESS);
      glfwGetCursorPos(window_, &cursor_x_, &cursor_y_);
    }
  }

  void handleMouseWheel(double wheel_x, double wheel_y) override
  {
    if (wheel_y < 0) {
      window_scale_ *= 1.1;
    }
    if (wheel_y > 0) {
      window_scale_ /= 1.1;
    }
    // std::cout << "WHEEL::" << wheel_x << ":::" << wheel_y << std::endl;
  }

  void handleKeyboardKey(int key, int scancode, int action, int mods) override
  {
    // std::cout << "KEYBOARD::" << key << ":::" << scancode << ":::" << action
    // << ":::" << mods << std::endl;
  }

private:
  std::unique_ptr<RenderList> render_list_ = nullptr;
  std::unique_ptr<ShaderProgram> shader_program_ = nullptr;

  GLint uniform_start_point_ = 0;

  float start_point_x_ = 0;
  float start_point_y_ = 0;

  GLint uniform_transform_matrix_ = 0;

  float window_start_x_ = 0;
  float window_start_y_ = 0;
  float window_scale_ = 1;

  bool movement_mode_ = false;

  double cursor_x_ = 0;
  double cursor_y_ = 0;
};
